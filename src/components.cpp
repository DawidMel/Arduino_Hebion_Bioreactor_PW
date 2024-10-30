#include "components.hpp"
#include "utility.hpp"
#include "eeprom_menager.hpp"


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



MeasuringDevice::MeasuringDevice(uint8_t read_pin,EepromVariable &zero_shift, EepromVariable &linear_factor) : 
m_read_pin(read_pin)
{
m_linear_factor = (linear_factor.retrieve_config_values_from_eeprom());
m_zero_shift = (zero_shift.retrieve_config_values_from_eeprom());
}

void MeasuringDevice::init()
{
    pinMode(m_read_pin, INPUT);
}
unsigned int MeasuringDevice::get_rav_measure()
{
    unsigned int temp_pin_voltage = analogRead(m_read_pin);
    return temp_pin_voltage;
} 


float MeasuringDevice::get_value()
{
    return 15;
} // TODO


void MeasuringDevice::set_zero_shift(EepromVariable &zero_shift,float new_value)
{
    if(new_value!=m_zero_shift)
    {
    m_zero_shift = new_value;
    zero_shift.change_eeprom_config_value(new_value);
    }
}
void MeasuringDevice::set_linear_factor(EepromVariable &linear_factor,float new_value)
{
    if(new_value!=m_linear_factor)
    {
    m_linear_factor = new_value;
    linear_factor.change_eeprom_config_value(new_value);
    }
}

float MeasuringDevice::get_zero_shift()
{return m_zero_shift;}
float MeasuringDevice::get_linear_factor()
{return m_linear_factor;}




Thermometer::Thermometer(uint8_t read_pin,EepromVariable &zero_shift, EepromVariable &linear_factor) :
 MeasuringDevice(read_pin, zero_shift, linear_factor)
{
}


float Thermometer::get_value() //TODO function implemented voltage -> value
{
    //not implemented;
    return 0;
} 


PhMeter::PhMeter(uint8_t read_pin,EepromVariable &zero_shift, EepromVariable &linear_factor) : 
MeasuringDevice(read_pin, zero_shift, linear_factor)
{
}

float PhMeter::get_value() //TODO function implemented voltage -> value
{
    //not implemented;
    return 0;
} 


OxygenMeter::OxygenMeter(uint8_t read_pin,EepromVariable &zero_shift, EepromVariable &linear_factor) :
 MeasuringDevice(read_pin, zero_shift, linear_factor)
{
}


float OxygenMeter::get_value() //TODO function implemented voltage -> value
{
    //not implemented;
    return 0;
} 
