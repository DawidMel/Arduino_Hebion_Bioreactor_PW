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
  uint8_t m_menu_depth = 0;


  uint8_t m_set_value_activator = 0;
  float m_temp_val = 0;


  unsigned long m_correction_timer =0;
  unsigned long m_sample_taking_timer = 0;

public:
MainController(float desire_ph, float max_ph_acceptable_deviation, 
               float desire_temp,float max_temp_acceptable_deviation,uint8_t max_menu_depth);


void calculate_correction_time(float current_ph);

void start_taking_sample(PeristalticPump &pump);
void stop_taking_sample(PeristalticPump &pump);

void start_correction(SimplePeristalticPump &pump);
void stop_correction(SimplePeristalticPump &pump);

uint8_t return_menu_depth() const;
void change_menu_depth(MyRotaryEncoder &encoder);

void set_config_value(float initial_value, float step, MyLCD &lcd, MyRotaryEncoder &encoder);
float return_temp_val();



};

class MeasuringController
{
private:
uint8_t m_allow_measurement = 0;
uint32_t m_measurement_interval = 2000; 
uint32_t m_last_measurement = 0;
public:
  MeasuringController();

  float measure(MeasuringDevice &dev);
  unsigned int rav_measure(MeasuringDevice &dev);
  float calculate_avg_from_meas(MeasureArray &measure_arr, MeasuringDevice &dev);
  float calculate_temperature_from_meas_avg(MeasureArray &measure_arr, Thermometer &term);
  float calculate_oxg_sat_from_meas_avg(MeasureArray &measure_arr, OxygenMeter &oxg, uint8_t temperature);
  float calculate_ph_from_meas_avg(MeasureArray &measure_arr, PhMeter &ph);
  void check_is_measure_ready();
  uint8_t get_measurement_state(); //TODO RENAME
  
};










#endif //STEERING_FUNCT