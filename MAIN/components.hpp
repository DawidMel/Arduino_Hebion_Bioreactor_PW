#include <Arduino.h>
#include <math.h>

#ifndef BIOREACTOR_COMPONENTS
#define BIOREACTOR_COMPONENTS

class PeristalticPump
{
  private:
    const int pwmPin;
    const int dir1Pin;
    const int dir2Pin;
    long currentPwmValue;

  public:
    PeristalticPump(int arg_PwmPin, int arg_Dir1Pin, int arg_Dir2Pin);
    void setPumpSpeed(int value); // from -100 (max reverse speed) to 100 (max forward speed)
    const long GetCurrentSpeed();
};

class MeasuringDevice
{
  private:
    const int read_pin;
    int value; // check what sensors return  TODO for now int ; but probably will be change in inheritance

  public:
    MeasuringDevice(int arg_read_pin);
    virtual int get_value();
};

class Thermometer : public MeasuringDevice
{
  public:
    Thermometer(int arg_read_pin);
    int get_value() override;
};

class PhMeter : public MeasuringDevice
{
  public:
    PhMeter(int arg_read_pin);
    int get_value() override;
};

class OxygenMeter : public MeasuringDevice
{
  public:
    OxygenMeter(int arg_read_pin);
    int get_value() override;
};

#endif // BIOREACTOR_COMPONENTS