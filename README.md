# Documentation
##
### MPS Project by:
[![](https://avatars1.githubusercontent.com/u/8987819?v=3&s=150)](https://github.com/DajanaS "Dajana Stojchevska") [![](https://avatars2.githubusercontent.com/u/18077884?v=4&s=150)](https://github.com/mtoshevska "Martina Toshevska") <br />
### Check out the final code [here](https://github.com/DajanaS/AirMeasurementsStatistics/blob/master/Final.c)
## 1. Description
Our project Air Measurement Statistics is intended for the Microcontroller PIC16F887 (frequency 8 Mhz). Once it is turned on, the user sees the menu on the `Glcd` screen (Graphic LCD). By using KeyPad the 4 different options from the menu can be chosen. Each is explained in the following paragraph.
## 2. Guide
### 2.1 KeyPad Menu & Home
KeyPad menu is using the following buttons: R0, R1, R2 and R3. The first one brings the user home no matter on which screen they are currently. The other three bring the user to three different screens: *Measured temperature*, *Temperature statistics* and *Warnings*, respectively.
### 2.2 Measure Temperature
On this screen the current temperature that the temperature sensor will measure will be shown.
### 2.3 Check Temperature Statistics
Considering the last N values (N in our program is 4) on this screen a graphic will be shown for each value in a form of a box.
### 2.4 Check Warnings
On this screen is shown a warning for the last measured temperature value. If it is in the range of normal temperatures on the screen will be written `OK`. If it is too high (above 30) it will be written `HIGH` and all 8 lights from portC will start flashing (alarming) that the temperature is not OK. Same will happen if it is too `LOW` (temperature is below -10).
## Conclusion and Further Work
There is place for improvement. Currently the program remembers and represents only the last 4 values because of the memory but this can be easily changed by changing the `N` value in the program.
