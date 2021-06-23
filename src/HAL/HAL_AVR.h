#pragma once

#if defined(ARDUINO_ARCH_AVR)

// some basic types
using uint8_t = unsigned char;
using int16_t = signed short;

static_assert(sizeof(int16_t) == 2);

#include "HAL/Common.h"

class HAL_AVR_Common : public HAL_Common {
public:
    HAL_AVR_Common(uint8_t pin);
protected:
    uint8_t mask;
    volatile uint8_t* reg_pin;
    volatile uint8_t* reg_port;
    volatile uint8_t* reg_ddr;
};

class HAL_AVR_EXT_PULLUP : public HAL_AVR_Common {
public:
    HAL_AVR_EXT_PULLUP(uint8_t pin);
    void BusDown();
    void BusUp();
    uint8_t BusRead();
    bool ResetPulse();
};

class HAL_AVR_INT_PULLUP : public HAL_AVR_Common {
public:
    HAL_AVR_INT_PULLUP(uint8_t pin);
    void BusDown();
    void BusUp();
    uint8_t BusRead();
    bool ResetPulse();
};

#if defined(MAXIMWIRE_EXTERNAL_PULLUP)
using HAL_AVR_Base = HAL_AVR_EXT_PULLUP;
#else
using HAL_AVR_Base = HAL_AVR_INT_PULLUP;
#endif

class HAL_AVR : public HAL_AVR_Base {
public:
    HAL_AVR(uint8_t pin)
        : HAL_AVR_Base(pin)
    {
    }

    uint8_t ReadSlot() {
        noInterrupts();
        BusDown();
        _delay_us(2);
        BusUp();
        _delay_us(5);
        uint8_t r = BusRead();
        interrupts();
        _delay_us(50);
        return r;
    }
    
    void WriteSlot0() {
        noInterrupts();
        BusDown();
        _delay_us(60);
        BusUp();
        interrupts();
        _delay_us(2);
    }
    
    void WriteSlot1() {
        noInterrupts();
        BusDown();
        _delay_us(2);
        BusUp();
        interrupts();
        _delay_us(60);
    }
};

using HAL = HAL_AVR;

#endif
