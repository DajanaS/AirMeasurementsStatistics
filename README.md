# Documentation
##
### MPS Project by:
[![](https://avatars1.githubusercontent.com/u/8987819?v=3&s=150)](https://github.com/DajanaS "Dajana Stojchevska") [![](https://avatars2.githubusercontent.com/u/18077884?v=4&s=150)](https://github.com/mtoshevska "Martina Toshevska") <br />
### Check out the final code [here](https://github.com/DajanaS/AirMeasurementsStatistics/blob/master/Final.c)
##
## 1. Description
Our project Air Measurement Statistics is intended for the Microcontroller PIC16F887 (frequency 8 Mhz). Once it is turned on, the user sees the menu on the `Glcd` screen (Graphic LCD). By using KeyPad the 4 different options from the menu can be chosen. Each is explained in the following paragraph.
## 2. Guide
### 2.1 KeyPad Menu & Home
KeyPad menu is using the following buttons: RA0, RA1, RA2 and RA3. The first one brings the user home no matter on which screen they are currently. The other three bring the user to three different screens: *Measured temperature*, *Temperature statistics* and *Warnings*, respectively.
### 2.2 Measure Temperature
On this screen the current temperature that the temperature sensor will measure will be shown.
### 2.3 Check Temperature Statistics
Considering the last N values (N in our program is 4) on this screen a graphic will be shown for each value in a form of a box.
### 2.4 Check Warnings
On this screen is shown a warning for the last measured temperature value. If it is in the range of normal temperatures on the screen will be written `OK`. If it is too high (above 30<sup>o</sup>C) it will be written `HIGH` and all 8 lights from portC will start flashing (alarming) that the temperature is not OK. Same will happen if it is too `LOW` (temperature is below -10<sup>o</sup>C).
## 3. Implementation
The main controlling component is the KeyPad Menu. Control transfers to other components (GLCD, LED lights, DS1820 sensor) based on the pressed button with call to the appropriate function: 
* measureTemperature() - this function reads current temperature from the DS1820 temperature sensor. The obtained value is unsigned integer. To be able to do manipulations with this value, it needs to be converted into signed integer. Afterwards, this value is displayed on GLCD and its level is displayed on the LEDs of portC. The range of the temperature obtained from the sensor is from -55<sup>o</sup>C to 125<sup>o</sup>C. This range is divided into eight parts, each representing one of the eight LEDs. For example, if temperature is 32<sup>o</sup>C, four, lights will be ON.
* showTemperatureStatistics() - temperature statistics is displayed on GLCD as a bar graphic. For each measured value, this function displays a box with height depending of the value. Temperature value is transformed from the range [-55;125] to the range [0;64]. Transformed value represents height of the corrrespondng box.
* checkWarning() - checks if measured temperature is in the range of normal temperature (from -10<sup>o</sup>C to 30<sup>o</sup>C in our program) and displays appropriate message on GLCD. If temperature is under minimum or over maximum, LEDs of portC start blinking.
## Conclusion and Further Work
There is place for improvement. Currently the program remembers and represents only the last 4 values because of the memory but this can be easily changed by changing the `N` value in the program.
