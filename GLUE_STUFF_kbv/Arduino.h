#ifndef ARDUINO_H
#define ARDUINO_H

#include <mbed.h>
#include "HardwareSerial.h"
#include "WString.h"

extern uint32_t SystemCoreClock;
#define F_CPU SystemCoreClock

#define PROGMEM
/*
#define PGM_P const char*
#define PSTR(x) x
#define pgm_read_byte(x)  (*(uint8_t *)(x))
#define pgm_read_word(x)  (*(uint16_t *)(x))
*/
#define delay(ms) wait_ms(ms)

extern uint32_t micros(void);
extern uint32_t millis(void);
extern void setup(void);
extern void loop(void);

#endif
