#ifndef STEERING_FUNCT
#define STEERING_FUNCT

class MainController
{
private:
  float m_desire_ph;
  float m_max_ph_acceptable_deviation;
  float m_desire_temp;
  float m_max_temp_acceptable_deviation;

  unsigned long m_correction_period;
  unsigned long m_sample_taking_period; //TODO MAY JUST PUT CONST HERE

  unsigned long m_correction_timer;
  unsigned long m_sample_taking_timer;
  
public:
MainController(float desire_ph, float max_ph_acceptable_deviation, 
               float desire_temp,float max_temp_acceptable_deviation);


void calculate_correction_time(float current_ph);

void start_taking_sample(PeristalticPump pump);
void stop_taking_sample(PeristalticPump pump);

void start_correction(SimplePeristalticPump pump);
void stop_correction(SimplePeristalticPump pump);

};





#endif //STEERING_FUNCT