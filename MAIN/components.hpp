#include <Arduino.h>
#include <math.h>

#ifndef BIOREACTOR_COMPONENTS
#define BIOREACTOR_COMPONENTS

class PeristalticPump
{
  private:
    const int m_pwmPin;
    const int m_dir1Pin;
    const int m_dir2Pin;
    long m_currentPwmValue;

  public:
    PeristalticPump(int PwmPin, int Dir1Pin, int Dir2Pin);
    void set_pump_speed(int value); // from -100 (max reverse speed) to 100 (max forward speed)
    long get_current_speed() const;
};

class MeasuringDevice
{
  private:
    const int m_read_pin;
    int m_value; // check what sensors return  TODO for now int ; but probably will be change in inheritance

  public:
    MeasuringDevice(int read_pin);
    virtual int get_value() const;
};

class Thermometer : public MeasuringDevice
{
  public:
    Thermometer(int read_pin);
    int get_value() const override;
};

class PhMeter : public MeasuringDevice
{
  public:
    PhMeter(int read_pin);
    int get_value() const override;
};

class OxygenMeter : public MeasuringDevice
{
  public:
    OxygenMeter(int read_pin);
    int get_value() const override;
};

#endif // BIOREACTOR_COMPONENTS