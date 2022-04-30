
# Nixie Tube Desk Clock

A six digit nixie tube desk clock Using the IN-12 nixie tubes. Programmed using the arduino platform. Uses a 3D printed case of a custom design with wooden dowels as feet.


## Features

- 12 hour or 24 hour time format
- hour, minute, and second readout
- keeps track of time when powered off
- Cathode Poisoning Protection - runs through all the digits every 5 minutes as part of a cathode poisoning protection routine


## Images
Nixie Tube Clock
https://github.com/AbdullahAttique/NixieClock/blob/main/clock%20image%20front.jpg
https://github.com/AbdullahAttique/NixieClock/blob/main/clock%20image%20side.jpg

PCB Schematic
https://github.com/AbdullahAttique/NixieClock/blob/main/Schematic_nixie%20board_2022-04-30.svg




## Technical Details
- 6 IN-12 nixie tubes.
- Arduino nano used for main processing.
- mounted to custom PCB with room for each component.
- DS3231 RTC module for time keeping. Can keep track of time when powered off using CR2032 battery.
- Uses 3 74HC595 shift registers for expanding IO to accomodate nixie tubes.
- 6 K155ID1 driver ICs. 1 per nixie tube.
- NCH6100HV for supplying high voltage
- Mini-360 step down buck converter for power supply voltage regulation
## Libraries Used
- RTC module library - DS3231
