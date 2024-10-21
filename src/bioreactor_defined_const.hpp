#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST

#include<Arduino.h>

//BUTTON SETTING - CAN BE CONFIGURABLE!
const char BUTTON_DEFAULT_STATE = 1; //mean pin state is HIGH
const long int BUTTON_STAY_ON_STATE = 2000; //[ms] time button dont change its state
const long int STAY_IN_MENU_TIME = 3000; //[ms] time after you can exit menu


//ROTARY ENCODER SETTINGS - CAN BE CONFIGURABLE!

const unsigned long SENSITIVITY = 150; // [ms] time after re will not change it state after did it before //TODO use better world :)


//LCD SETTINGS
// for now not available

//SENSOR DESIRE PARAMETER - CAN BE CONFIGURABLE!
const float DESIRE_PH = 7;
const float MAX_PH_ACCEPTABLE_DEVIATION = 0.5;
const float DESIRE_TEMP = 21.37;
const float MAX_TEMP_ACCEPTABLE_DEVIATION = 4.2069;


//LCD PHYSICAL CONNECTION
// TODO

//SD CARD READER PHYSICAL CONNECTION
constexpr uint8_t CS_PIN = 10;
constexpr uint8_t DEF_MOSI_PIN = 11;
constexpr uint8_t DEF_MISO_PIN = 12;
constexpr uint8_t DEF_SCK_PIN = 13;
#define FILENAME "m.txt"

//ROTARY ENCODER PHYSICAL CONNECTION
constexpr uint8_t RE_PIN_A = 3;
constexpr uint8_t RE_PIN_B = 4;
constexpr uint8_t RE_BUTTON_PIN = 5;

//SENSORS PHYSICAL CONNECTION
constexpr uint8_t PH_METER_PIN = A1;
constexpr uint8_t THERMOMETER_PIN = A2;        
constexpr uint8_t OXYGEN_METER_PIN = A3;

//SAMPLE PUMP PARAMETER (this pump is peristaltic and work only in on/off mode)
constexpr int PUMP_FLOW_SPEED = 60; //[ml/min]
constexpr int SAMPLE_SIZE = 2; //[ml]
constexpr int PUMP_SAMPLE_TAKING_TIME = int(float(SAMPLE_SIZE)/float(PUMP_FLOW_SPEED)*60*1000); //[ms]; should be 2000ms

//PH KEEPERS PUMP _PH_CORRECTION - CAN BE CONFIGURABLE!
const long int TIME_BETWEEN_PH_CORRECTION = 10000; //[ms] time between ph correction [TODO change name]
const long int CORRECTION_TIME = 100; // [ms] initial time of correction
const float MULT_PER_DEGREE = 3; // it mean if  desire ph is 6 and we have 8 time of pump activate will be 100*3*3 = 900 ms
const long int MAX_REACTION_TIME = 3000;  //max time of open the pump



// thermometer parameter (it is hardware parameter)
const long int THERMISTOR_NOMINAL = 10000;        // [ohm] resistance at 25 degrees C
const uint8_t TEMPERATURE_NOMINAL = 25;          // temp. for nominal resistance (almost always 25 C)
const long int B_COEFFICIENT = 3950;              // [UNIT!] The beta coefficient of the thermistor (usually 3000-4000)
const long int SERIES_RESISTOR = 10000;           // [ohm] the value of the 'other' resistor     



#endif // BIOREACTOR_CONST