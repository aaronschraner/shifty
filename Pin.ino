#include "Pin.h"
#include <Arduino.h>
#include <pins_arduino.h>
#include <wiring_private.h>

//update values to modify the new pin number
void Pin::setPin(int pinNum)
{
  this->pinNum = pinNum;
  byte port = digitalPinToPort(pinNum);
  mask = digitalPinToBitMask(pinNum);
  ddrreg = *portModeRegister(port);
  portreg = *portOutputRegister(port);
  pinreg = *portInputRegister(port);
}

//set registers and values
Pin::Pin(int pinNum):
  pinNum(pinNum),
  ddrreg(*portModeRegister(digitalPinToPort(pinNum))),
  portreg(*portOutputRegister(digitalPinToPort(pinNum))),
  pinreg(*portInputRegister(digitalPinToPort(pinNum))),
  mask(digitalPinToBitMask(pinNum))
{
  if(pinNum < 0)
    mask = 0;
}

//do the other thing but also set direction
Pin::Pin(int pinNum, byte direct):
  Pin(pinNum)
{
  setDirection(direct);
}

//do the things and also set direction and value
Pin::Pin(int pinNum, byte direct, bool value):
  Pin(pinNum)
{
  setDirection(direct);
  setValue(value);
}

//IMPORTANT: sets pin as input
//be careful about multiple pins referencing the same
//pin number and being destroyed at different times
Pin::~Pin()
{
  setDirection(INPUT);
  setValue(0);
}

//basically digitalRead but slightly faster
inline bool Pin::getValue() const
{
  return pinreg & mask;
}

//ditto but for digitalWrite
inline void Pin::setValue(bool value)
{
  portreg = (portreg & ~mask) | (value ? mask : 0);
  //delay(100);
}

//ditto but for pinMode (supports INPUT_PULLUP)
inline void Pin::setDirection(byte direct)
{
  ddrreg = (ddrreg & ~mask) | (direct ? mask : 0);
  portreg = direct == INPUT_PULLUP ? portreg | mask : portreg & ~ mask;
}

//digitalRead but pretty
inline Pin::operator bool() const
{
  return getValue();
}

//digitalWrite but pretty
inline bool Pin::operator=(bool value)
{
  setValue(value);
  return value;
}


