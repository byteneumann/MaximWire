
# MaximWire

This is very simple library to connect DS18B20 temperature sensors and Arduino controllers.

This fork adds two universal HAL implementation making the library usable with (m)any Arduino controller(s):

* HAL\_Arduino: based on Arduino functions (pinMode, digitalRead, delayMicroseconds).
* HAL\_AVR: based on AVR Libc functions and direct port access (PINx, PORTx, DDRx, \_delay\_us).

HAL_AVR can save you some bytes but does less checks. Use with caution.

Getting started
---------------

By default, if you use only one DS18B20 device, you probably need an external pull-up resistor of 4.7kOhm. If the internal pull-up resistance is low enough, you may do without one.

* +3.3V -> RED
* BUS   -> YELLOW
* GND   -> BLACK

And connect BUS and +3.3V lines with pull-up resistor.

Where BUS is any digital ping (like 9, for example).
And use example from examples/AnyDevice.

Select or overwrite your HAL by defining MAXIMWIRE_HAL.

Multiple devices
----------------

When you need to work with multiple devices on the same bus, you need external pull-up resistor of 1.7~2.2kOm.

* +3.3V -> RED1 + RED2 + ...
* BUS   -> YELLOW1 + YELLOW2 + ... 
* GND   -> BLACK1 + BLACK2 + ...

And connect BUS and +3.3V lines with pull-up resistor.

Parasite power
--------------

DS18B20 are able to share bus wire for powering itself, so only two wires required. And you will need external pullup resistor too.

* BUS -> YELLOW
* GND -> RED + BLACK

And connect BUS and +3.3V lines with pull-up resistor.

