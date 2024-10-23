#include <Arduino.h>
#include <math.h>
#include "bioreactor_defined_const.hpp"
#include "utility.hpp"

#ifndef BIOREACTOR_COMPONENTS
#define BIOREACTOR_COMPONENTS


class SimplePeristalticPump
{
private:
uint8_t m_pin_forward;
unsigned int m_correction_time;


public:
SimplePeristalticPump(uint8_t pin_forward);
void init();
void run();
void stop();
};

class PeristalticPump 
{
  private:
    const uint8_t m_pwm_pin;
    const uint8_t m_motor_negative_pin;
    const uint8_t m_motor_positive_pin;
    int m_current_pwm_value;

  public:
    PeristalticPump(uint8_t pwm_pin, uint8_t motor_negative_pin, uint8_t motor_positive_pin);
    void init();
    void set_pump_speed(int value); // from -100 (max reverse speed) to 100 (max forward speed)
    long get_current_speed() const;
    void start_taking_sample();
    void stop_taking_sample();
};

class MeasuringDevice
{
  //TODO: add virtual destructor even empty
  protected:
    const int m_read_pin;
    float m_value; // check what sensors return  TODO for now int ; but probably will be change in inheritance

  public:
    MeasuringDevice(uint8_t read_pin);
    void init();
    virtual float get_value();
};

class Thermometer : public MeasuringDevice
{
  public:
    Thermometer(uint8_t read_pin);
    float get_value() override;
};

class PhMeter : public MeasuringDevice
{
  public:
    PhMeter(uint8_t read_pin);
    float get_value() override;
};

class OxygenMeter : public MeasuringDevice
{
  public:
    OxygenMeter(uint8_t read_pin);
    float get_value() override;
};

#endif // BIOREACTOR_COMPONENTS