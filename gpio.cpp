#include <lgpio.h>
#include "gpio.h"


Gpio::Gpio(QObject *parent) : QObject(parent)
{
    m_handle = lgGpiochipOpen(0);
    int init_lvl = 0;
    for(int pin : LEDS)
        lgGpioClaimOutput(m_handle, LFLAGS, pin, init_lvl);
}


Gpio::~Gpio()
{
    int state = 0;
    for (int pin : LEDS)
        lgGpioWrite(m_handle, pin, state);

    lgGpiochipClose(m_handle);
}


void Gpio::set(int pin,bool value)
{
    lgGpioWrite(m_handle, pin, value);
}


void Gpio::set(unsigned int pattern)
{
    int n = 0;
    bool value;
    unsigned int proof = 0b0001;
    for(auto pin : LEDS)
    {
        value = proof & pattern >> n;
        lgGpioWrite(m_handle, pin, value);
        n++;
    }
}
