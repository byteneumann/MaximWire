#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>

namespace MaximWire {

#include "HAL_AVR.h"

HAL_AVR_Common::HAL_AVR_Common(uint8_t pin)
    : HAL_Common(pin)
{
    mask = digitalPinToBitMask(_Pin);
    const uint8_t port = digitalPinToPort(_Pin);
    reg_pin = portInputRegister(port);
    reg_port = portOutputRegister(port);
    reg_ddr = portModeRegister(port);
}

HAL_AVR_EXT_PULLUP::HAL_AVR_EXT_PULLUP(uint8_t pin)
    : HAL_AVR_Common(pin)
{
    *reg_ddr &= ~mask;
    *reg_port &= ~mask;
}

void HAL_AVR_EXT_PULLUP::BusDown() {
    *reg_ddr |= mask;
    //*reg_port &= ~mask;
}

void HAL_AVR_EXT_PULLUP::BusUp() {
    *reg_ddr &= ~mask;
}

uint8_t HAL_AVR_EXT_PULLUP::BusRead() {
    return (*reg_pin & mask) ? HIGH : LOW;
}

bool HAL_AVR_EXT_PULLUP::ResetPulse() {
    uint16_t deadline = 200;
    for (; deadline > 0 && BusRead() == 0; --deadline)
        _delay_us(1);
    if (deadline) {
        BusDown();
        _delay_us(480);
        cli();
        BusUp();
        deadline = 480;
        for (; deadline > 0 && BusRead() != 0; --deadline)
            _delay_us(1);
        for (; deadline > 0 && BusRead() == 0; --deadline)
            _delay_us(1);
        sei();
        if (deadline) {
            for (; deadline > 0; --deadline)
                _delay_us(1);
            return true;
        }
    }
    return false;
}

HAL_AVR_INT_PULLUP::HAL_AVR_INT_PULLUP(uint8_t pin)
    : HAL_AVR_Common(pin)
{
    *reg_ddr &= ~mask;
    *reg_port |= mask;
}

void HAL_AVR_INT_PULLUP::BusDown() {
    *reg_port &= ~mask;
}

void HAL_AVR_INT_PULLUP::BusUp() {
    //*reg_ddr &= ~mask;
    *reg_port |= mask;
}

uint8_t HAL_AVR_INT_PULLUP::BusRead() {
    return (*reg_pin & mask) ? HIGH : LOW;
}

bool HAL_AVR_INT_PULLUP::ResetPulse() {
    BusDown();
    _delay_us(480);
    BusUp();
    cli();
    uint16_t deadline = 480;
    for (; deadline > 0 && BusRead() != 0; --deadline)
        _delay_us(1);
    for (; deadline > 0 && BusRead() == 0; --deadline)
        _delay_us(1);
    sei();
    if (deadline) {
        for (; deadline > 0; --deadline)
            _delay_us(1);
        return true;
    }
    return false;
}

}

#endif