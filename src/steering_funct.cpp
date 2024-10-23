# include "steering_funct.hpp"
# include "bioreactor_defined_const.hpp"
#include "components.hpp"


MainController::MainController(float desire_ph, float max_ph_acceptable_deviation, 
                               float desire_temp,float max_temp_acceptable_deviation)
                               :
m_desire_ph(desire_ph), m_max_ph_acceptable_deviation(max_ph_acceptable_deviation),
m_desire_temp(desire_temp), m_max_temp_acceptable_deviation(max_temp_acceptable_deviation)
{
}

void MainController::calculate_correction_time(float current_ph) //TODO find better algorithm like PID controller
{

    float temp_exponent = 0;
    temp_exponent = abs(current_ph - m_desire_ph);

    m_correction_period = long(pow(MULT_PER_DEGREE, temp_exponent) * CORRECTION_TIME);
    if(m_correction_period>MAX_REACTION_TIME)
    {
        m_correction_period=MAX_REACTION_TIME;
    }
}

void MainController::start_taking_sample(PeristalticPump pump)
{   
    if (m_sample_taking_timer + m_sample_taking_period < millis()) //if not taking sample
    {
        m_sample_taking_timer = millis();
        pump.start_taking_sample();                                //take it
    }
}
void MainController::stop_taking_sample(PeristalticPump pump)
{
    if(m_sample_taking_timer + m_sample_taking_period < millis())
    {
        pump.stop_taking_sample();
    }
}
void MainController::start_correction(SimplePeristalticPump pump)
{
    if (m_correction_timer + m_correction_period < millis()) //if not taking sample
    {
        m_correction_timer = millis();
        pump.run();                                //take it
    }
}
void MainController::stop_correction(SimplePeristalticPump pump)
{
    if(m_correction_timer + m_correction_period < millis())
    {
        pump.stop();
    }
}