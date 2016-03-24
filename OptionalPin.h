#ifndef OPTIONALPIN_H
#define OPTIONALPIN_H
#include "Pin.h"



class OptionalPin
{
  private:
    //bool m_exists;
    Pin* pin;
  public:
    bool exists() const { return pin; }
    OptionalPin():pin(0) {}
    OptionalPin(Pin& p): pin(&p) {}
    Pin* operator->() {return pin;}

    //things copied from Pin.h

    inline bool getValue() const { return pin->getValue();}
    inline void setValue(bool value) { pin->setValue(value); }
    inline void setDirection(byte direct) { pin->setDirection(direct); }
    
    explicit inline operator bool() const { return (bool)*pin; } //like digitalRead
    inline bool operator=(bool value) { return *pin = value; } //like digitalWrite
    bool operator==(const Pin& p) { return *pin == p; } //returns true if pin numbers match
    int getNum() const { return pin->getNum(); } //returns pin number

} NOPIN;

#endif

