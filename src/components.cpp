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
void SimplePeristalticPump::stabilize_ph(float current_ph, float desire_ph)
{
    float temp_exponent = 1;
    if (current_ph > desire_ph)
    {
        temp_exponent = current_ph - desire_ph;
    }
    else
    {
        temp_exponent = desire_ph - current_ph;
    }

    long delay_time = long(pow(MULT_PER_DEGREE, temp_exponent) * CORRECTION_TIME);
    if(delay_time>MAX_REACTION_TIME)
    {
        delay_time=MAX_REACTION_TIME;
    }
    Serial.print("PH: ");
    Serial.println(current_ph);
    Serial.println(delay_time);
    digitalWrite(m_pin_forward, HIGH);
    delay(delay_time);
    digitalWrite(m_pin_forward, LOW);
}




PeristalticPump::PeristalticPump(uint8_t pwm_pin, uint8_t dir1_pin, uint8_t dir2_pin)
    : m_pwm_pin(pwm_pin), m_dir1_pin(dir1_pin), m_dir2_pin(dir2_pin)
{
}

void PeristalticPump::init()
{
    pinMode(m_pwm_pin, OUTPUT);
    pinMode(m_dir1_pin, OUTPUT);
    pinMode(m_dir2_pin, OUTPUT);
}

void PeristalticPump::set_pump_speed(int value) // probably need to define an alternative method for the pump
{
    if (value >= 0) // TODO - add validation of value (should be in range 0 to 100)
    {
        digitalWrite(m_dir1_pin, HIGH);
        digitalWrite(m_dir2_pin, LOW);
    }
    else
    {
        digitalWrite(m_dir1_pin, LOW);
        digitalWrite(m_dir2_pin, HIGH);
    }

    m_current_pwm_value = map(value, -100, 100, -255, 255);
    analogWrite(m_pwm_pin, abs(m_current_pwm_value));
}
long PeristalticPump::get_current_speed() const
{
    return m_current_pwm_value;
}

void PeristalticPump::take_sample()
{
    digitalWrite(m_pwm_pin,HIGH);
    delay(PUMP_SAMPLE_TAKING_TIME);
    digitalWrite(m_pwm_pin,LOW);
}



MeasuringDevice::MeasuringDevice(int read_pin) : m_read_pin(read_pin)
{
}

void MeasuringDevice::init()
{
    pinMode(m_read_pin, INPUT);
}
float MeasuringDevice::get_value()
{
    return 10;
} // TODO

Thermometer::Thermometer(int read_pin) : MeasuringDevice(read_pin)
{
}

float Thermometer::get_value()
{
    return 10;
} // TODO use real measure function

PhMeter::PhMeter(int read_pin) : MeasuringDevice(read_pin)
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

OxygenMeter::OxygenMeter(int read_pin) : MeasuringDevice(read_pin)
{
}

float OxygenMeter::get_value()
{
    return 10;
} // TODO use real measure function