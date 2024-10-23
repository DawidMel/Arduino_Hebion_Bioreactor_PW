#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST

#include<Arduino.h>

//SAMPLE PUMP PHYSICAL CONNECTION
constexpr uint8_t PP_MOTOR_NEGATIVE_PIN = 2;
constexpr uint8_t PP_PWM_PIN = 3;
constexpr uint8_t PP_MOTOR_POSITIVE_PIN = 4;

//ALKALINE PUMP PHYSICAL CONNECTION
constexpr uint8_t ALKALINE_PUMP_PIN = 5;

//ACID PUMP PHYSICAL CONNECTION
constexpr uint8_t ACID_PUMP_PIN = 6;

//ROTARY ENCODER PHYSICAL CONNECTION
constexpr uint8_t RE_CLK_PIN = 7;
constexpr uint8_t RE_DT_PIN = 8;
constexpr uint8_t RE_BUTTON_PIN = 9;

//SD CARD READER PHYSICAL CONNECTION
constexpr uint8_t SD_CS_PIN = 10;
constexpr uint8_t SD_MOSI_PIN = 11;
constexpr uint8_t SD_MISO_PIN = 12;
constexpr uint8_t SD_SCK_PIN = 13;

//SENSORS PHYSICAL CONNECTION
constexpr uint8_t PH_METER_PIN = A1;
constexpr uint8_t THERMOMETER_PIN = A2;        
constexpr uint8_t OXYGEN_METER_PIN = A3;

//LCD PHYSICAL CONNECTION 
constexpr uint8_t LCD_SDA_PIN = 18; //physical connected with A4 (more specific is it 1 microcontroller pin)
constexpr uint8_t LCD_SCL_pin = 19; //physical connected with A5 (more specific is it 1 microcontroller pin)

// FREE PIN :
// AREF - NOTE THAT IT IS NOT PROGRAMABLE PIN it is just reference voltage for A/D Converter
// constexpr uint8_t A0_NAME = A0
// constexpr uint8_t RX_NAME = 0
// constexpr uint8_t TX_NAME = 1

//BUTTON INITIAL SETTING
constexpr uint8_t BUTTON_DEFAULT_STATE = 1; //mean pin state is HIGH
constexpr unsigned long BUTTON_STAY_ON_STATE = 2000; //[ms] time button dont change its state
constexpr unsigned long STAY_IN_MENU_TIME = 3000; //[ms] time after you can exit menu


//ROTARY ENCODER SETTINGS - CAN BE CONFIGURABLE!
constexpr unsigned long SENSITIVITY = 300; // [ms] time after re will not change it state after did it before //TODO use better world :)

//SENSOR DESIRE PARAMETER - CAN BE CONFIGURABLE!
constexpr float DESIRE_PH = 7;
constexpr float MAX_PH_ACCEPTABLE_DEVIATION = 0.5;
constexpr float DESIRE_TEMP = 21.37;
constexpr float MAX_TEMP_ACCEPTABLE_DEVIATION = 4.2069;

//SAMPLE PUMP PARAMETER (this pump is peristaltic and work only in on/off mode)
constexpr float PUMP_FLOW_SPEED = 60.0; //[ml/min]
constexpr float SAMPLE_SIZE = 2.0; //[ml]
constexpr long PUMP_SAMPLE_TAKING_TIME = long(((SAMPLE_SIZE)/(PUMP_FLOW_SPEED))*60.0*1000.0); //[ms]; should be 2000ms

//PH KEEPERS PUMP _PH_CORRECTION
constexpr unsigned long TIME_BETWEEN_PH_CORRECTION = 10000; //[ms] time between ph correction [TODO change name]
constexpr unsigned long CORRECTION_TIME = 100; // [ms] initial time of correction
constexpr float MULT_PER_DEGREE = 3; // it mean if  desire ph is 6 and we have 8 time of pump activate will be 100*3*3 = 900 ms
constexpr unsigned long MAX_REACTION_TIME = 3000;  //max time of open the pump

// thermometer parameter (it is hardware parameter)
constexpr long int THERMISTOR_NOMINAL = 10000;        // [ohm] resistance at 25 degrees C
constexpr uint8_t TEMPERATURE_NOMINAL = 25;          // temp. for nominal resistance (almost always 25 C)
constexpr long int B_COEFFICIENT = 3950;              // [UNIT!] The beta coefficient of the thermistor (usually 3000-4000)
constexpr long int SERIES_RESISTOR = 10000;           // [ohm] the value of the 'other' resistor     

//LCD SETTINGS
// for now not available


//FILE WITH DATA
#define SD_FILENAME "m.txt"

#endif // BIOREACTOR_CONST