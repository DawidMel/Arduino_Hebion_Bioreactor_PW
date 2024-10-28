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

uint8_t MainController::return_menu_depth() const
{
    return m_menu_depth;
}

void MainController::change_menu_depth(MyRotaryEncoder encoder)
{
    uint8_t button_state = encoder.get_button_state();
    if(button_state == LOW) //if button pressed
    {
        m_menu_depth+=1;
        if(m_menu_depth > m_max_menu_depth)
        {
            m_menu_depth = 0;
        }
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

/*

    // PH VALUE FORMULA
    voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
    pHValue = 3.5 * voltage + Offset;




    // TEMPERATURE FORMULA TODO REMOVE THIS SENSOR BECAUSE THIS SUCK A LOT!

      // convert the value to resistance

//idea your thermometer is in serial with resistor of knowing resistance 
// it make voltage divider, we measure voltage on 
float return_temp(float voltage_measure)
{
  voltage_measure = 1023 / voltage_measure - 1;  
  voltage_measure = SERIES_RESISTOR / voltage_measure;



  // formula when we measure voltage from Rt
 //  V = Rt/(Rt+Rs) * Vcc
 //  Rt= V/Vcc * (Rt+Rs)
 //  Rt * (1-V/Vcc) = V/Vcc*Rs
  // Rt = V/(Vcc-V)*Rs
  // where V is analogRead Vcc is maximum value of A/D converter (in arduino it is 1023)

  thermistor_resistance = voltage_measure/(1023-voltage_measure)*THERMISTOR_NOMINAL;


  float steinhart;                                       //TODO hell of optimization but fuck it
  steinhart = thermistor_resistance / THERMISTOR_NOMINAL;          // (R/Ro)
  steinhart = log(steinhart);                         // ln(R/Ro)
  steinhart /= B_COEFFICIENT;                        // 1/B * ln(R/Ro)
  steinhart += 1.0 / (THERMISTOR_NOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // convert absolute temp to C

  TemperatureValue = steinhart;
  return TemperatureValue;
}

//oxygen formula 

#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution

//Single-point calibration Mode=0
//Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0

#define READ_TEMP (25) //Current water temperature ℃, Or temperature sensor function

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //mv
#define CAL1_T (25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

    // alternative
    // to get best parameter in range 15-35 celsius degree we can use linearyzation with  a=-154,6753247	 b=12216,40693 max err in range 2,1%
    // to get best parameter in range 10-40 celsius degree we can use linearyzation with a=-158,0846774	b=12415,02016 max err in range 5%
    // to get best parameter in range 0-40 celsius degree we can use linearyzation with a=-194,6550523	 b=13453,83275  max err in range 12%



int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif



*/