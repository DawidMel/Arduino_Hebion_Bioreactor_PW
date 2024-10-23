#include "components.hpp"
#include "utility.hpp"


SimplePeristalticPump::SimplePeristalticPump(uint8_t pin_forward) :
m_pin_forward(pin_forward)
{
}
void SimplePeristalticPump::init()
{
    pinMode(m_pin_forward,OUTPUT);
}


void SimplePeristalticPump::run()
{
    digitalWrite(m_pin_forward, HIGH);
}

void SimplePeristalticPump::stop()
{
    digitalWrite(m_pin_forward, LOW);
}




PeristalticPump::PeristalticPump(uint8_t pwm_pin, uint8_t motor_negative_pin, uint8_t motor_positive_pin)
    : m_pwm_pin(pwm_pin), m_motor_negative_pin(motor_negative_pin), m_motor_positive_pin(motor_positive_pin)
{
}

void PeristalticPump::init()
{
    pinMode(m_pwm_pin, OUTPUT);
    pinMode(m_motor_negative_pin, OUTPUT);
    pinMode(m_motor_positive_pin, OUTPUT);
}

void PeristalticPump::set_pump_speed(int value) // probably need to define an alternative method for the pump
{
    if (value >= 0) // TODO - add validation of value (should be in range 0 to 100)
    {
        digitalWrite(m_motor_negative_pin, HIGH);
        digitalWrite(m_motor_positive_pin, LOW);
    }
    else
    {
        digitalWrite(m_motor_negative_pin, LOW);
        digitalWrite(m_motor_positive_pin, HIGH);
    }

    m_current_pwm_value = map(value, -100, 100, -255, 255);
    analogWrite(m_pwm_pin, abs(m_current_pwm_value));  //TODO IS IT PWM? need check driver setting
}
long PeristalticPump::get_current_speed() const
{
    return m_current_pwm_value;
}

void PeristalticPump::start_taking_sample() //just use max available speed of pump
{
    digitalWrite(m_pwm_pin,HIGH); //TODO change to something none blocking
}

void PeristalticPump::stop_taking_sample() //just use max available speed of pump
{
    digitalWrite(m_pwm_pin,LOW); //TODO change to something none blocking
}



MeasuringDevice::MeasuringDevice(uint8_t read_pin) : m_read_pin(read_pin)
{
}

void MeasuringDevice::init()
{
    pinMode(m_read_pin, INPUT);
}
float MeasuringDevice::get_value() const
{
    return 10;
} // TODO

Thermometer::Thermometer(uint8_t read_pin) : MeasuringDevice(read_pin)
{
}

float Thermometer::get_value()
{
    return 10;
} // TODO use real measure function

PhMeter::PhMeter(uint8_t read_pin) : MeasuringDevice(read_pin)
{
    pinMode(m_read_pin, INPUT);
}

float PhMeter::get_value()
{
    float temp_voltage = analogRead(m_read_pin);
    Serial.print("temp_voltage mess: ");
    Serial.println(temp_voltage);
    m_value = 3.5 * temp_voltage / 1023 * 5.0;
    return m_value;
} // TODO use real measure function

OxygenMeter::OxygenMeter(uint8_t read_pin) : MeasuringDevice(read_pin)
{
}

float OxygenMeter::get_value()
{
    return 10;
} // TODO use real measure function