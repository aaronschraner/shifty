#include "Shift595.h"

//Shift595::Shift595(Pin &clockPin, Pin &dataPin, int clearPin, int latchPin, int enablePin):
//  clockPin(clockPin), dataPin(dataPin)
//{
//  //if pin number is < 0, set Pin to nullptr, otherwise set it up
//  this->clearPin  =  clearPin  >= 0 ? new Pin(clearPin,  OUTPUT, HIGH) : 0; //start with clear high (don't clear)
//  this->latchPin  =  latchPin  >= 0 ? new Pin(latchPin,  OUTPUT, HIGH) : 0; //start with latch high (passthrough)
//  this->enablePin =  enablePin >= 0 ? new Pin(enablePin, OUTPUT, HIGH) : 0; //start with output disabled (enable is active low)
//}

Shift595::Shift595(Pin& clockPin, Pin& dataPin, OptionalPin clearPin, OptionalPin latchPin, OptionalPin enablePin):
  clockPin(clockPin),
  dataPin(dataPin),
  clearPin(clearPin),
  latchPin(latchPin),
  enablePin(enablePin)
{
  clockPin.setDirection(OUTPUT);
  dataPin.setDirection(OUTPUT);
  if (clearPin.exists())
  {
    clearPin->setDirection(OUTPUT);
    clearPin->setValue(HIGH);
  }
  if (latchPin.exists())
  {
    latchPin->setDirection(OUTPUT);
    latchPin->setValue(HIGH);
  }
  if (enablePin.exists())
  {
    enablePin->setDirection(OUTPUT);
    enablePin->setValue(HIGH);
  }

}

Shift595::~Shift595()
{
//  //destroy pins
//  if (!pinsExternal)
//  {
//    delete &clockPin;
//    delete &dataPin;
//    if (clearPin)  delete clearPin;
//    if (latchPin)  delete latchPin;
//    if (enablePin) delete enablePin;
//  }
}

//reset register outputs to 0
void Shift595::clear()
{
  //if async clear is present, use it
  if (hasClear())
  {
    clearPin = 0;
    clearPin = 1;
    update();
  }
  else
  {
    //otherwise shift out 0's
    shift(0);
  }
}

//enable the outputs
void Shift595::enable(bool en)
{
  if (hasEnable())
  {
    enablePin = !en; //enable is active low
  }
}

//disable the outputs
void Shift595::disable()
{
  enable(0); //disable
}

//shift out <b> and update outputs
void Shift595::shift(byte b)
{
  load(b);
  update();
}

//load b into the register serially (don't update outputs yet)
void Shift595::load(byte b)
{
  nload<byte>(b, 8);
}

//load an arbitrary number of bits into the register serially
template <typename T>
void Shift595::nload(T b, byte bits, uint8_t order)
{
  T mask = (order==MSBFIRST) ? 1 << (bits - 1) : 1;
  for (byte i=0; i < bits; i++)
  {
    clockPin = LOW;
    dataPin = (bool)(mask & b);
    clockPin = HIGH;
    mask = (order==MSBFIRST) ? mask >> 1 : mask << 1;
    
  }
}

//update the output latches
void Shift595::update()
{
  if (hasLatch())
  {
   latchPin = LOW;
   latchPin = HIGH;
  }
}

