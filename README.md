# Iron-man-Mark-I
Iron Man Arc reactor code based on https://www.thingiverse.com/thing:2069812  
[Project video](https://www.youtube.com/watch?v=1DcfSf4Fniw)  

## Introduction
The Mark I Arc Reactor consists of a 3D printed housing where 2 LED rings are embedded inside. These rings produce different light modes of different durations based on user input. 

The input can be a manual toggle via a pushbutton or any Android bluetooth capable device using google voice. The LED rings are controlled by three daisy chained shift registers, and voice input is done via a HC-05 bluetooth module. Along with each mode, there is a corresponding audio file that plays via a speaker in sync with the selected mode.
 
The audio complexity was the only feature I was not able to integrate with the system.
### Complexities

    Shift Registers
        -Successfully implemented the controlling of each of the three shift registers outputs to toggle specific LEDs
    HC-05 Bluetooth module
        -Able to Serialize voice input to toggle through the modes
    Speaker/Audio
        -Unable to integrate at this time
 
 
## User Guide
If not using the bluetooth feature, simply use the pushbutton to toggle between modes.
To use Bluetooth via an Android phone download the AMR_Voice app on the play store.
After downloading, make sure the arc reactor is on. Enter the app, use the menu button to open up a navigation tab then click on “connect robot” and select the bluetooth device titled “HC-05”. Then use any key word corresponding to the specific mode wanted.
Hardware Components Used

Quantity,Component

1, Arduino Uno R3

3, 8-Bit Shift Register

10,Red LED

9,White LED

16,220 Ω Resistor

1,HC-05 Bluetooth Module

1,1 kΩ Resistor

1,2 kΩ Resistor

1, Pushbutton
 
## Software Libraries Used
<ShiftRegister74HC595.h>

The library functions allow for a user-friendly interface to control each shift register’s output pins. I can select individual pins and check current pin states which makes programming each light mode infinitely easier.

<SoftwareSerial.h>

Allows for the HC-05 Bluetooth Module’s serialized voice commands to be transmitted to the microcontroller.

##  [Wiring Diagram](https://github.com/lpurgitoryl/Iron-man-Mark-I/blob/main/project_deatils/schematics_arc_reactor/schematics_arc_reactor.pdf)
