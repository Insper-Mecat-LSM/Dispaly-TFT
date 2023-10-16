#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_

#include "mbed.h"
#include <Serial.h>
#include "Print.h"

class HardwareSerial : public Print, Serial
{
public:
    HardwareSerial(PinName tx, PinName rx) : Serial(tx, rx) {}
    void begin(unsigned long baud)
    {
        Serial::baud(baud);
    }
    using Print::write; // pull in write(str) and write(buf, size) from Print
    //virtual size_t write(uint8_t);
    virtual size_t write(uint8_t c) { return Serial::_putc(c); }

private:
};

extern HardwareSerial serial_kbv;

#endif
