#include <Arduino.h>
#include <math.h>


#ifndef BIOREACTOR_COMPONENTS
#define BIOREACTOR_COMPONENTS

class Peristaltic_pump
{
  private:
  const int pwmPin;
  const int dir1Pin;
  const int dir2Pin;
  long currentPwmValue;

  public:
  Peristaltic_pump(int arg_PwmPin, int arg_Dir1Pin, int arg_Dir2Pin);
  void setPumpSpeed(int value);  //from -100 (max reverse speed) to 100 (max forward speed)
  int GetCurrentSpeed();
};


class Component
{
  private:
  const int read_pin;
  int value; //check what sensors return  TODO for now int ; but probably will be change in inheritance 

  public:
  Component(int arg_read_pin);
  virtual int get_value();
};



class ComponentThermometer : public Component
{
  public:
  ComponentThermometer(int arg_read_pin);
  int get_value() override;
};


class Component_ph_meter : public Component
{
  public:
  Component_ph_meter(int arg_read_pin);
  int get_value() override;
};


class Component_oxygenmeter : public Component
{
  public:
  Component_oxygenmeter(int arg_read_pin);
  int get_value() override;
};


#endif //BIOREACTOR_COMPONENTS