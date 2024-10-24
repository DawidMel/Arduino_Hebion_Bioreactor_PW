#include <Arduino.h>
# include "components.hpp"
# include "my_encoder.hpp"

#ifndef STEERING_FUNCT
#define STEERING_FUNCT

class MainController
{
private:
  float m_desire_ph;
  float m_max_ph_acceptable_deviation;
  float m_desire_temp;
  float m_max_temp_acceptable_deviation;
  uint8_t m_max_menu_depth;

  unsigned long m_correction_period = 0;
  unsigned long m_sample_taking_period = 0; //TODO MAY JUST PUT CONST HERE
  uint8_t m_menu_state = 0;


  unsigned long m_correction_timer =0;
  unsigned long m_sample_taking_timer = 0;

public:
MainController(float desire_ph, float max_ph_acceptable_deviation, 
               float desire_temp,float max_temp_acceptable_deviation,uint8_t max_menu_depth);


void calculate_correction_time(float current_ph);

void start_taking_sample(PeristalticPump pump);
void stop_taking_sample(PeristalticPump pump);

void start_correction(SimplePeristalticPump pump);
void stop_correction(SimplePeristalticPump pump);

uint8_t return_menu_state() const;
void change_menu_state(my_rotary_encoder encoder);

unsigned int measure_temperature(Thermometer Therm1);
unsigned int measure_PH(PhMeter phm1);
unsigned int measure_Oxygen_amount(OxygenMeter oxm1);

float calculate_average_from_measurement(float linear_factor,float zero_shift, float average);

};





#endif //STEERING_FUNCT