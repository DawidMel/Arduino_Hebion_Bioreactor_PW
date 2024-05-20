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


public:
SimplePeristalticPump(uint8_t pin_forward);
void init();
void stabilize_ph(float current_ph,float desire_ph);
};

class PeristalticPump 
{
  private:
    const uint8_t m_pwmPin;  //TODO snakekase
    const uint8_t m_dir1Pin;
    const uint8_t m_dir2Pin;
    int m_currentPwmValue;

  public:
    PeristalticPump(uint8_t PwmPin, uint8_t Dir1Pin, uint8_t Dir2Pin);  //TODO rename variable
    void init();
    void set_pump_speed(int value); // from -100 (max reverse speed) to 100 (max forward speed)
    long get_current_speed() const;
    void take_sample();
};

class MeasuringDevice
{
  //TODO: add virtual destructor even empty
  protected:
    const int m_read_pin;
    float m_value; // check what sensors return  TODO for now int ; but probably will be change in inheritance

  public:
    MeasuringDevice(int read_pin);
    void init();
    virtual float get_value();
};

class Thermometer : public MeasuringDevice
{
  public:
    Thermometer(int read_pin);
    float get_value() override;
};

class PhMeter : public MeasuringDevice
{
  public:
    PhMeter(int read_pin);
    float get_value() override;
};

class OxygenMeter : public MeasuringDevice
{
  public:
    OxygenMeter(int read_pin);
    float get_value() override;
};

#endif // BIOREACTOR_COMPONENTS