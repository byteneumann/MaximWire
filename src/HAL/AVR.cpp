#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>

namespace MaximWire {

#include "AVR.h"

HAL_AVR_EXT_PULLUP::HAL_AVR_EXT_PULLUP(uint8_t pin)
    : HAL_Common(pin)
{
	pinMode(_Pin, INPUT);
}

void HAL_AVR_EXT_PULLUP::BusDown() {
	pinMode(_Pin, OUTPUT);
    digitalWrite(_Pin, LOW);
}

void HAL_AVR_EXT_PULLUP::BusUp() {
	pinMode(_Pin, INPUT);
}

uint8_t HAL_AVR_EXT_PULLUP::BusRead() {
	return digitalRead(_Pin);
}

bool HAL_AVR_EXT_PULLUP::ResetPulse() {
    unsigned long now = micros();
    unsigned long deadline = now + 200;
    while (BusRead() == 0 && (now = micros()) < deadline) {}
    if (now < deadline) {
        BusDown();
        delayMicroseconds(480);
        noInterrupts();
        BusUp();
        now = micros();
        deadline = now + 480;
        while (BusRead() != 0 && (now = micros()) < deadline) {}
        while (BusRead() == 0 && (now = micros()) < deadline) {}
        interrupts();
        if (now < deadline) {
            delayMicroseconds(deadline - now);
            return true;
        }
    }
    return false;
}

HAL_AVR_INT_PULLUP::HAL_AVR_INT_PULLUP(uint8_t pin)
    : HAL_Common(pin)
{
	pinMode(_Pin, INPUT_PULLUP);
}

void HAL_AVR_INT_PULLUP::BusDown() {
    pinMode(_Pin, INPUT);
}

void HAL_AVR_INT_PULLUP::BusUp() {
    pinMode(_Pin, INPUT_PULLUP);
}

uint8_t HAL_AVR_INT_PULLUP::BusRead() {
    return digitalRead(_Pin);
}

bool HAL_AVR_INT_PULLUP::ResetPulse() {
    BusDown();
    delayMicroseconds(480);
    BusUp();
    noInterrupts();
    unsigned long now = micros();
    unsigned long deadline = now + 480;
    while (BusRead() != 0 && (now = micros()) < deadline) {}
    while (BusRead() == 0 && (now = micros()) < deadline) {}
    interrupts();
    if (now < deadline) {
        delayMicroseconds(deadline - now);
        return true;
    }
    return false;
}

}

#endif