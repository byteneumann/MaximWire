#pragma once

#if defined(ARDUINO_ARCH_AVR)

// some basic types
using uint8_t = unsigned char;
using int16_t = signed short;

static_assert(sizeof(int16_t) == 2);

#include "HAL/Common.h"

class HAL_Arduino_EXT_PULLUP : public HAL_Common {
public:
    HAL_Arduino_EXT_PULLUP(uint8_t pin);
    void BusDown();
    void BusUp();
    uint8_t BusRead();
    bool ResetPulse();
};

class HAL_Arduino_INT_PULLUP : public HAL_Common {
public:
    HAL_Arduino_INT_PULLUP(uint8_t pin);
    void BusDown();
    void BusUp();
    uint8_t BusRead();
    bool ResetPulse();
};

#if defined(MAXIMWIRE_EXTERNAL_PULLUP)
using HAL_Arduino_Base = HAL_Arduino_EXT_PULLUP;
#else
using HAL_Arduino_Base = HAL_Arduino_INT_PULLUP;
#endif

class HAL_Arduino : public HAL_Arduino_Base {
public:
    HAL_Arduino(uint8_t pin)
        : HAL_Arduino_Base(pin)
    {
    }

    uint8_t ReadSlot() {
        noInterrupts();
        BusDown();
        delayMicroseconds(2);
        BusUp();
        delayMicroseconds(5);
        uint8_t r = BusRead();
        interrupts();
        delayMicroseconds(50);
        return r;
    }
    
    void WriteSlot0() {
        noInterrupts();
        BusDown();
        delayMicroseconds(60);
        BusUp();
        interrupts();
        delayMicroseconds(2);
    }
    
    void WriteSlot1() {
        noInterrupts();
        BusDown();
        delayMicroseconds(2);
        BusUp();
        interrupts();
        delayMicroseconds(60);
    }
};

using HAL = HAL_Arduino;

#endif
