#include "Shift595.h"
byte sevseg(byte value)
{
  static const byte segdigits[] = {
    0b1111110,
    0b0110000,
    0b1101101,
    0b1111001,
    0b0110011,
    0b1011011,
    0b1011111,
    0b1110000,
    0b1111111,
    0b1111011,
    0b1110111,
    0b0011111,
    0b1001110,
    0b0111101,
    0b1001111,
    0b1000111
  };
  return segdigits[value % 16];
}

void setup() {

  Pin clock = 12, data = 13, latch = 10, clear = 11;

  Shift595 myShifter(clock, data, clear, latch, NOPIN);
  
  while (true)
    for (int i = 0; i < 16; i++)
    {
      myShifter = ~sevseg(i);
      clock = LOW;
      delay(1000);
    }

}

void loop() {}
