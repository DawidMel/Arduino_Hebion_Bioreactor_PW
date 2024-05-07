#include "components.hpp"

Peristaltic_pump::Peristaltic_pump(int arg_PwmPin, int arg_Dir1Pin, int arg_Dir2Pin):
pwmPin(arg_PwmPin),
dir1Pin(arg_Dir1Pin),
dir2Pin(arg_Dir2Pin)
{}

void Peristaltic_pump::setPumpSpeed(int value)   //możliwe że będzie trzeba zdefinować alternatywną metodę dla pompy :)
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

    currentPwmValue = (value, -100, 100, -255, 255);
    analogWrite(pwmPin, abs(currentPwmValue));
}

int Peristaltic_pump::GetCurrentSpeed() {return currentPwmValue;}



Component::Component(int arg_read_pin):
read_pin(arg_read_pin)
{}
int Component::get_value() {return 10;} //TODO


Component_termometr::Component_termometr(int arg_read_pin):
Component(arg_read_pin)
{}
int Component_termometr::get_value() 
{
  static int a = 10;
  a+=1;
  return a;
  } //TODO


Component_ph_meter::Component_ph_meter(int arg_read_pin):
Component(arg_read_pin)
{}
int Component_ph_meter::get_value(){return 10;} //TODO


Component_oxygenmeter::Component_oxygenmeter(int arg_read_pin):
Component(arg_read_pin)
{}
int Component_oxygenmeter::get_value() {return 10;}