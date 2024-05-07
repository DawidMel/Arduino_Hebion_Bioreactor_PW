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

int Peristaltic_pump::GetCurrentSpeed() 
{
  return currentPwmValue;
}



