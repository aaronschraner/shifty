#shifty
###A simple to use shift register library for Arduino
##Usage:
#####This library uses a custom Pin class for reasons that were more clear to me a week ago
To use the shift register, you must first create pins for at least the clock (CLK) and data (DS) connections
on the 74hc595 shift register. You can also add asynchronous reset, output latch, and output enable pins. 
```Arduino
Pin clock(12);
Pin data(13);
Pin latch(10);
```
Next use the pins to create a shift register object.
```Arduino
Shift595 shifty(clock, data, NOPIN, latch);
```
Functions for controlling the register are shown in Shift595.h
The simplest way to use shifty is to use the builtin operator overloading functionality.
```Arduino
shifty = 0b11100010; //sends a binary "11100010" to the shift register
```
An example is given in [Shift595_test.ino](https://github.com/aaronschraner/shifty/Shift595_test.ino).

