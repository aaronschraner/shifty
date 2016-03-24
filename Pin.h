#ifndef PIN_H
#define PIN_H
/*
 * 
 * IMPORTANT NOTE
 * 
 * This only works with AVR-based boards. The SAM-based Arduino DUE 
 * uses a different scheme for dealing with pins
 * that is all.
 */
class Pin
{
  protected:
    //registers for pin manipulation
    volatile uint8_t &ddrreg, &portreg, &pinreg;
    byte mask; //relevant bits
    int pinNum; //pin number
  public:
    //set the number of this Pin
    void setPin(int pinNum);

    //initialize registers
    Pin(int pinNum);

    //initialize registers and direction
    Pin(int pinNum, byte direct);

    //initialize registers, direction, and value
    Pin(int pinNum, byte direct, bool value);

    //set pin as an input
    ~Pin();
    
    inline bool getValue() const;
    inline void setValue(bool value);
    inline void setDirection(byte direct);
    
    explicit inline operator bool() const; //like digitalRead
    inline bool operator=(bool value); //like digitalWrite
    //inline int operator=(int value);
    //inline bool operator==(bool v) { return getValue() == v; }
    //inline bool operator!=(bool v) { return getValue() != v; }
    bool operator==(const Pin& p) { return p.pinNum == pinNum; } //returns true if pin numbers match
    int getNum() const { return pinNum; } //returns pin number
};

#endif
