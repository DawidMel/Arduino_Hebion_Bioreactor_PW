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



class Component  //TODO jak okaze sie ze zbieranie i interpretacja wynikow bedzie inna zastosowac dziedziczenie i indywidualne metody
{
  private:
  const int read_pin;
  int value; //sprawdzić co zwraca termometr TODO na razi zaloze int

  public:
  Component(int arg_read_pin);
  virtual int get_value();
};

class term1 : Component
{
  int get_value() override 
  {
    static int a = 60;
    a+=1;
    return a;
  }
};



#endif //BIOREACTOR_COMPONENTS