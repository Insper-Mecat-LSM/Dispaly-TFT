// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License

#ifndef _TOUCHSCREEN_KBV_MBED_H_
#define _TOUCHSCREEN_KBV_MBED_H_
#include <stdint.h>

class TSPoint_kbv {
    public:
        TSPoint_kbv(void);
        TSPoint_kbv(int16_t x, int16_t y, int16_t z);

        bool operator==(TSPoint_kbv);
        bool operator!=(TSPoint_kbv);

        int16_t x, y, z;
};

class TouchScreen_kbv {
    public:
#if defined(__MBED__)
        TouchScreen_kbv(PinName xp, PinName yp, PinName xm, PinName ym, uint16_t rx = 0);
#else
        TouchScreen_kbv(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx = 0);
#endif
//        bool isTouching(void);
        uint16_t pressure(void);
        int readTouchY();
        int readTouchX();
        TSPoint_kbv getPoint();
        int16_t pressureThreshhold;

    private:
#if defined(__MBED__)
        uint16_t analogRead(PinName p);
        void pinModeVal(PinName p, uint8_t mode, uint8_t val); 
        PinName _yp, _ym, _xm, _xp;
#else
        void pinModeVal(uint8_t p, uint8_t mode, uint8_t val); 
        uint8_t _yp, _ym, _xm, _xp;
#endif
        uint16_t _rxplate;
};

#endif


