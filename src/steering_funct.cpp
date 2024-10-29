# include "steering_funct.hpp"
# include "bioreactor_defined_const.hpp"
#include "components.hpp"


MainController::MainController(float desire_ph, float max_ph_acceptable_deviation, 
                               float desire_temp,float max_temp_acceptable_deviation,uint8_t max_menu_depth)
                               :
m_desire_ph(desire_ph), m_max_ph_acceptable_deviation(max_ph_acceptable_deviation),
m_desire_temp(desire_temp), m_max_temp_acceptable_deviation(max_temp_acceptable_deviation),
m_max_menu_depth(max_menu_depth)
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

void MainController::start_taking_sample(PeristalticPump &pump)
{   
    if (m_sample_taking_timer + m_sample_taking_period < millis()) //if not taking sample
    {
        m_sample_taking_timer = millis();
        pump.start_taking_sample();                                //take it
    }
}
void MainController::stop_taking_sample(PeristalticPump &pump)
{
    if(m_sample_taking_timer + m_sample_taking_period < millis())
    {
        pump.stop_taking_sample();
    }
}
void MainController::start_correction(SimplePeristalticPump &pump)
{
    if (m_correction_timer + m_correction_period < millis()) //if not taking sample
    {
        m_correction_timer = millis();
        pump.run();                                //take it
    }
}
void MainController::stop_correction(SimplePeristalticPump &pump)
{
    if(m_correction_timer + m_correction_period < millis())
    {
        pump.stop();
    }
}

uint8_t MainController::return_menu_depth() const
{
    return m_menu_depth;
}

void MainController::change_menu_depth(MyRotaryEncoder &encoder)
{
    uint8_t button_state = encoder.get_button_state();
    if(button_state == LOW) //if button pressed
    {
        Serial.println("button_pressed");
        m_menu_depth++;
        if(m_menu_depth > m_max_menu_depth)
        {
            m_menu_depth = 0;
        }
        Serial.println(m_menu_depth);
    }

}

void MainController::set_config_value(float initial_value, float step, MyLCD &lcd , MyRotaryEncoder &encoder)
{
    static int prev_menu_state = 0;
    static int menu_state = 0;

    menu_state += encoder.get_encoder_move();

    if (menu_state != prev_menu_state) 
    {
        lcd.clear();
        lcd.send_float_value("new value:",initial_value+step*menu_state,0);
        prev_menu_state = menu_state;
    }

    if(m_set_value_activator = 1)
    {
        m_temp_val = (initial_value+step*menu_state);
        prev_menu_state = 0;
        menu_state = 0;

    }
}

float MainController::return_temp_val()
{
    return m_temp_val;
}




MeasuringController::MeasuringController()
{
}

float MeasuringController::measure(MeasuringDevice &dev)
{
    return dev.get_value();
}

unsigned int MeasuringController::rav_measure(MeasuringDevice &dev)
{
    return dev.get_rav_measure();
}


float MeasuringController::calculate_avg_from_meas(MeasureArray &measure_arr, MeasuringDevice &dev)
{
    float zero_shift = dev.get_zero_shift();
    float linear_factor = dev.get_linear_factor();
    int meas_avg = measure_arr.get_average();

    // TODO implement code for different variant of measurement

    return (meas_avg*linear_factor+zero_shift);
}


  float MeasuringController::calculate_ph_from_meas_avg(MeasureArray &measure_arr, PhMeter &ph)
  {
        // PH VALUE FORMULA easy and simple :) like it
    float voltage = measure_arr.get_average() * 5.0 / 1023;
    float pHValue = 3.5 * voltage;
    return (pHValue*ph.get_linear_factor() + ph.get_zero_shift());
  }


  float MeasuringController::calculate_temperature_from_meas_avg(MeasureArray &measure_arr, Thermometer &term)
  {
    // CALCULATE TEMPERATURE level of irritation implementing this = NAGOTUJCE MI GAR BIGOSU

    //idea your thermometer is in serial with resistor of knowing resistance 
    // it make voltage divider, we measure voltage drop on thermometer

    // formula when we measure voltage from Rt and we want get resistance of Rt

    //  V = Rt/(Rt+Rs) * Vcc | * ((Rt+Rs)/Vcc)
    //  Rt= V/Vcc * (Rt+Rs)  | - (V/Vcc * Rt)
    //  Rt * ((1-V)/Vcc) = V/Vcc*Rs  | * (Vcc/(1-V))
    //  Rt = V/(Vcc-V)*Rs
    //  where V is analogRead Vcc is maximum value of A/D converter (in arduino it is 1023)

  float voltage_measure =  measure_arr.get_average();           // NOT MAKE PROPERTY BECAUSE IT SHOULD BE GEOMETRIC AVERAGE 
                                                                // because logarithmic operation to obtain best precision we should also include
                                                                // non linear formula to calculate Thermistor resistance
  float thermistor_resistance = voltage_measure/(1023-voltage_measure)*THERMISTOR_NOMINAL;

//  using Steinhart–Hart equation

// 1/T = 1/T0 + (1/B)*(Ln(Rt/R0))
// T = 1/(1/T0 + (1/B)*(Ln(Rt/R0)))
// T = 1/(B/(T0*B)) + (T0/(B*T0))*(Ln(Rt/R0)))
// T = (B*T0)/B+T0(Ln(R/R0))
// to convert in to C degree just subtract 273,15

  float temperature;   
  temperature =  (B_COEFFICIENT*TEMPERATURE_NOMINAL)/
  (B_COEFFICIENT +  TEMPERATURE_NOMINAL*log(thermistor_resistance / THERMISTOR_NOMINAL))-273,15;   

  return temperature;

  }



  float MeasuringController::calculate_oxg_sat_from_meas_avg(MeasureArray &measure_arr, OxygenMeter &oxg, uint8_t temperature)
  {


    #define VREF 5000    //VREF (mv)
    #define ADC_RES 1024 //ADC Resolution

    //Two-point calibration needs to be filled CAL2_V and CAL2_T
    //CAL1 High temperature point, CAL2 Low temperature point
    // for fully saturated solution
    #define CAL1_V (1600) //mv
    #define CAL1_T (25)   //℃
    #define CAL2_V (1300) //mv
    #define CAL2_T (15)   //℃


    const uint16_t DO_Table[41] = {                         //temperature from 0 to 40 C degree
        14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
        11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
        9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
        7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

    // alternative
    // to get best parameter in range 15-35 celsius degree we can use linearization with  a=-154,6753247; b=12216,40693 max err in range 2,1%
    // to get best parameter in range 10-40 celsius degree we can use linearization with a=-158,0846774; b=12415,02016 max err in range 5%
    // to get best parameter in range 0-40 celsius degree we can use linearization with a=-194,6550523; b=13453,83275  max err in range 12%

        
    float voltage_mv = measure_arr.get_average()*5.0/1023;

    uint16_t V_saturation = (int16_t)((int8_t)temperature - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
    return (voltage_mv * DO_Table[temperature] / V_saturation);
  }

  void MeasuringController::check_is_measure_ready()
  {
        m_allow_measurement = 0;
    if(millis()>(m_last_measurement+m_measurement_interval))
    {
        m_allow_measurement = 1;
        m_last_measurement = millis();
    }
  }
  uint8_t MeasuringController::get_measurement_state()
  {
    return m_allow_measurement;

  }








