#include "Pin.h"
#include "OptionalPin.h"
#ifndef SHIFT595_H
#define SHIFT595_H
/*
 * 74hc595 pinout for reference
 * 
 *  16151413121110 9 
 *  _|_|_|_|_|_|_|_|_
 * |_                |
 * |_) 74HC595N    O |
 * |_________________|
 *   | | | | | | | |
 *   1 2 3 4 5 6 7 8
 *       __ __
 * Q1 --|1 U16|-- Vcc
 * Q2 --|2  15|-- Q0
 * Q3 --|3  14|-- DS
 * Q4 --|4  13|-- OE_L
 * Q5 --|5  12|-- STCP
 * Q6 --|6  11|-- SHCP
 * Q7 --|7  10|-- MR_L
 * GND--|8___9|-- Q7S
 */


//class for using the 74hc595 shift register
class Shift595
{
    //ayy
  private:

    Pin &clockPin, //SHCP, serial clock
        &dataPin;  //DS. serial data
    OptionalPin clearPin, //MR_L, asynchronous reset - active low
                latchPin, //STCP, latch clock - clock for output latches
                enablePin;//OE_L. output enable - active low
    
  public:
    
    Shift595(Pin& clockPin, Pin& dataPin, int clearPin = -1, int latchPin = -1, int enablePin = -1); //DON'T USE UNLESS YOU MUST
    //Shift595(Pin& clockPin, Pin& dataPin):clockPin(clockPin), dataPin(dataPin) {} 
    Shift595(Pin& clockPin, Pin& dataPin, OptionalPin clearPin=NOPIN, OptionalPin latchPin=NOPIN, OptionalPin enablePin=NOPIN);
    
    ~Shift595();

    //do I have clear functionality?
    inline bool hasClear()  const {
      return clearPin.exists();
    }
    //do I have output latches?
    inline bool hasLatch()  const {
      return latchPin.exists();
    }
    //do I have an enable pin?
    inline bool hasEnable() const {
      return enablePin.exists();
    }
    
    void clear(); //reset latch (updates values, works even if no clearPin exists)
    void enable(bool en = 1); //enable latch (or set to en if given)
    void disable(); //disable latch
    void shift(byte b); //load and output b
    inline void load(byte b); //send b serially to the register
    template <typename T>
    void nload(T val, byte nbits, uint8_t bitorder=LSBFIRST); //send an arbitrary number of bits (good for chains)
    void update(); //update the output latches
    byte operator=(const byte& b) { //shift(b)
      shift(b);
      return b;
    }


};

#endif
