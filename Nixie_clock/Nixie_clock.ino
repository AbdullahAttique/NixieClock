
#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;

// set time using DS3231_set code example

bool h12;
bool PM;

unsigned long prevTime = millis();

byte digits[6] = {0,0,0,0,0,0};
byte hour;
byte minute;
byte second;

const int latchPin = 5;
const int clockPin = 4;
const int dataPin = 6;

bool invert = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

}

void loop() {

  //cathode poisoning protection
  unsigned long currentTime = millis();
  //every 5 minutes, run through all digits
  if (currentTime - prevTime > 300000){
    for (int i = 0; i<10; i++){
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 0);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 1);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 2);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 3);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 4);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 5);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 6);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 7);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 8);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
      cycle(dataPin, clockPin, 9);
      digitalWrite(latchPin, HIGH);
      delay(100);
    }
    prevTime = millis();
  }

  //convert to 12 hour format
  int hour12 = Clock.getHour(h12,PM);
  if (hour12 > 12){
    hour12 = hour12-12; 
  }
  if (hour12 == 0){
    hour12 = 12;
  }

  //fill digit array with time
  digits[0] = firstDigit(hour12);
  digits[1] = secondDigit(hour12);
  digits[2] = firstDigit(Clock.getMinute());
  digits[3] = secondDigit(Clock.getMinute());
  digits[4] = firstDigit(Clock.getSecond());
  digits[5] = secondDigit(Clock.getSecond());

  //convert to appropriate bytes
  hour = makeByte(digits[1], digits[0]);
  minute = makeByte(digits[3], digits[2]);
  second = makeByte(digits[5], digits[4]);

  //write to shift registers
  digitalWrite(latchPin, LOW);
  
  shiftOut(dataPin, clockPin, MSBFIRST, second);
  shiftOut(dataPin, clockPin, MSBFIRST, minute);
  shiftOut(dataPin, clockPin, MSBFIRST, hour);

  digitalWrite(latchPin, HIGH);
  
}





//concatenate the two digit bytes
byte makeByte(int first, int second){
  return((first<<4)+second);
}

//create byte from first digit
int firstDigit(int num){
  return (num/10) % 10;
}

//create byte from second digit
int secondDigit(int num){
  return (num % 10);
}

//sends number to cycle
void cycle(int datapin, int clockpin, int number){
  byte output = makeByte(number, number);
  shiftOut(datapin, clockpin, MSBFIRST, output);
  shiftOut(datapin, clockpin, MSBFIRST, output);
  shiftOut(datapin, clockpin, MSBFIRST, output);
}
