// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// adapted from (c) ladyada / adafruit

#include "Arduino.h"

#include "TouchScreen_kbv_mbed.h"

#define NUMSAMPLES 3  //.kbv
#if defined(__STM32F1__) || defined(ESP32)  //Maple core
#define ADC_ADJUST >>2
#else
#define ADC_ADJUST
#endif

TSPoint_kbv::TSPoint_kbv(void)
{
    x = y = 0;
}

TSPoint_kbv::TSPoint_kbv(int16_t x0, int16_t y0, int16_t z0)
{
    x = x0;
    y = y0;
    z = z0;
}

bool TSPoint_kbv::operator==(TSPoint_kbv p1)
{
    return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
}

bool TSPoint_kbv::operator!=(TSPoint_kbv p1)
{
    return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
}

static void insert_sort(int array[], uint8_t size)
{
    uint8_t j;
    int save;

    for (int i = 1; i < size; i++) {
        save = array[i];
        for (j = i; j >= 1 && save < array[j - 1]; j--)
            array[j] = array[j - 1];
        array[j] = save;
    }
}

// ***** conditional for MBED *****
#if defined(__MBED__)
TouchScreen_kbv::TouchScreen_kbv(PinName xp, PinName yp, PinName xm, PinName ym, uint16_t rxplate)
{
    _yp = yp;
    _xm = xm;
    _ym = ym;
    _xp = xp;
    _rxplate = rxplate;

    pressureThreshhold = 10;
}

uint16_t TouchScreen_kbv::analogRead(PinName p)
{
    AnalogIn _adc(p);
    return _adc.read_u16() >> 6;    // MBED gives 16-bit
}

void TouchScreen_kbv::pinModeVal(PinName p, uint8_t mode, uint8_t val)
{
    DigitalInOut _out(p);
    if (mode) {
        _out.output();
        _out.write(val);
    } else {
        _out.input();
        _out.mode(PullNone);
    }
}
#else
TouchScreen_kbv::TouchScreen_kbv(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate)
{
    _yp = yp;
    _xm = xm;
    _ym = ym;
    _xp = xp;
    _rxplate = rxplate;

    pressureThreshhold = 10;
}

void TouchScreen_kbv::pinModeVal(uint8_t p, uint8_t mode, uint8_t val)
{
    pinMode(p, mode);
    digitalWrite(p, val);
}
#endif
// ******** end of conditional ****

TSPoint_kbv TouchScreen_kbv::getPoint(void)
{
    int x, y, z;
    int samples[NUMSAMPLES];
    uint8_t i, valid = 1;
    
    pinModeVal(_yp, 0, 0);
    pinModeVal(_ym, 0, 0);
    pinModeVal(_xp, 1, 1);
    pinModeVal(_xm, 1, 0);

    for (i = 0; i < NUMSAMPLES; i++) {
        samples[i] = analogRead(_yp) ADC_ADJUST;
    }
    insert_sort(samples, NUMSAMPLES);
    x = (1023 - samples[NUMSAMPLES / 2]); //choose median

    pinModeVal(_xp, 0, 0);
    pinModeVal(_xm, 0, 0);
    pinModeVal(_yp, 1, 1);
    pinModeVal(_ym, 1, 0);

    for (i = 0; i < NUMSAMPLES; i++) {
        samples[i] = analogRead(_xm) ADC_ADJUST;
    }

    insert_sort(samples, NUMSAMPLES);

    y = (1023 - samples[NUMSAMPLES / 2]);

    pinModeVal(_xp, 1, 0); // Set X+ to ground
    pinModeVal(_xm, 0, 0); // Hi-Z
    pinModeVal(_yp, 0, 0); // Hi-Z
    pinModeVal(_ym, 1, 1); // Set Y- to VCC

    int z1 = analogRead(_xm) ADC_ADJUST;
    int z2 = analogRead(_yp) ADC_ADJUST;

    z = (1023 - (z2 - z1));

    // *** these two lines would ensure XM, YP are in Digital mode ***
    //pinModeVal(_xm, 1, 1); // OUTPUT HIGH
    //pinModeVal(_yp, 1, 1); // OUTPUT HIGH

    return TSPoint_kbv(x, y, z);  //XM, YP still in ANALOG mode
}

int TouchScreen_kbv::readTouchX(void)
{
    pinModeVal(_yp, 0, 0);
    pinModeVal(_ym, 0, 0);
    pinModeVal(_xp, 1, 1);
    pinModeVal(_xm, 1, 0);

    return (1023 - (analogRead(_yp)) ADC_ADJUST);
}

int TouchScreen_kbv::readTouchY(void)
{
    pinModeVal(_xp, 0, 0);
    pinModeVal(_xm, 0, 0);
    pinModeVal(_yp, 1, 1);
    pinModeVal(_ym, 1, 0);

    return (1023 - (analogRead(_xm)) ADC_ADJUST);
}

uint16_t TouchScreen_kbv::pressure(void)
{
    pinModeVal(_xp, 1, 0); // Set X+ to ground
    pinModeVal(_xm, 0, 0); // Hi-Z
    pinModeVal(_yp, 0, 0); // Hi-Z
    pinModeVal(_ym, 1, 1); // Set Y- to VCC

    int z1 = analogRead(_xm) ADC_ADJUST;
    int z2 = analogRead(_yp) ADC_ADJUST;

    return (1023 - (z2 - z1));
}
