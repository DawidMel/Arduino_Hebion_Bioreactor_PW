#include "components.hpp"

PeristalticPump::PeristalticPump(int PwmPin, int Dir1Pin, int Dir2Pin)
    : m_pwmPin(PwmPin), m_dir1Pin(Dir1Pin), m_dir2Pin(Dir2Pin)
{
}

void PeristalticPump::set_pump_speed(int value) // probably need to define an alternative method for the pump
{
    if (value >= 0) //TODO - add validation of value (should be in range 0 to 100)
    {
        digitalWrite(m_dir1Pin, HIGH);
        digitalWrite(m_dir2Pin, LOW);
    }
    else
    {
        digitalWrite(m_dir1Pin, LOW);
        digitalWrite(m_dir2Pin, HIGH);
    }

    m_currentPwmValue = map(value, -100, 100, -255, 255);
    analogWrite(m_pwmPin, abs(m_currentPwmValue));
}
long PeristalticPump::get_current_speed() const
{
    return m_currentPwmValue;
}

MeasuringDevice::MeasuringDevice(int read_pin) : m_read_pin(read_pin)
{
}
int MeasuringDevice::get_value() const
{
    return 10;
} // TODO

Thermometer::Thermometer(int read_pin) : MeasuringDevice(read_pin)
{
}

int Thermometer::get_value() const
{
    return 10;
} // TODO use real measure function

PhMeter::PhMeter(int read_pin) : MeasuringDevice(read_pin)
{
}

int PhMeter::get_value() const
{
    return 10;
} // TODO use real measure function

OxygenMeter::OxygenMeter(int read_pin) : MeasuringDevice(read_pin)
{
}

int OxygenMeter::get_value() const
{
    return 10;
} // TODO use real measure function