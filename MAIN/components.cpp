#include "components.hpp"

PeristalticPump::PeristalticPump(int arg_PwmPin, int arg_Dir1Pin, int arg_Dir2Pin)
    : pwmPin(arg_PwmPin), dir1Pin(arg_Dir1Pin), dir2Pin(arg_Dir2Pin)
{
}

void PeristalticPump::setPumpSpeed(int value) // probably need to define an alternative method for the pump
{
    if (value >= 0)
    {
        digitalWrite(dir1Pin, HIGH);
        digitalWrite(dir2Pin, LOW);
    }
    else
    {
        digitalWrite(dir1Pin, LOW);
        digitalWrite(dir2Pin, HIGH);
    }

    currentPwmValue = map(value, -100, 100, -255, 255);
    analogWrite(pwmPin, abs(currentPwmValue));
}
long PeristalticPump::getCurrentSpeed() const
{
    return currentPwmValue;
}

MeasuringDevice::MeasuringDevice(int arg_read_pin) : read_pin(arg_read_pin)
{
}
int MeasuringDevice::get_value() const
{
    return 10;
} // TODO

Thermometer::Thermometer(int arg_read_pin) : MeasuringDevice(arg_read_pin)
{
}

int Thermometer::get_value() const
{
    static int a = 10;
    a += 1;
    return a;
} // TODO use real measure function

PhMeter::PhMeter(int arg_read_pin) : MeasuringDevice(arg_read_pin)
{
}

int PhMeter::get_value() const
{
    return 10;
} // TODO use real measure function

OxygenMeter::OxygenMeter(int arg_read_pin) : MeasuringDevice(arg_read_pin)
{
}

int OxygenMeter::get_value() const
{
    return 10;
} // TODO use real measure function