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







#endif //BIOREACTOR_COMPONENTS