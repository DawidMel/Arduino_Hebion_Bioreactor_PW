#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST


//BUTTON SETTING
#define BUTTON_DEFAULT_STATE 1 //mean pin state is HIGH
#define BUTTON_STAY_ON_STATE 2000 //[ms] time button dont change its state
#define STAY_IN_MENU_TIME 3000 //[ms] time after you can exit menu


//ROTARY ENCODER SETTINGS

#define SENSITIVITY 150 // [ms] time after re will not change it state after did it before //TODO use better world :)


//LCD SETTINGS
// for now not available

//SENSOR DESIRE PARAMETER 
#define DESIRE_PH 7
#define MAX_PH_ACCEPTABLE_DEVIATION 0.5
#define DESIRE_TEMP 21.37
#define MAX_TEMP_ACCEPTABLE_DEVIATION 4.2069


//LCD PHYSICAL CONNECTION
// TODO

//SD CARD READER PHYSICAL CONNECTION
#define CS_PIN 10
#define DEF_MOSI_PIN 11
#define DEF_MISO_PIN 12
#define DEF_SCK_PIN 13
#define FILENAME "m.txt"

//ROTARY ENCODER PHYSICAL CONNECTION
#define RE_PIN_A 3
#define RE_PIN_B 4
#define RE_BUTTON_PIN 5

//SENSORS PHYSICAL CONNECTION
#define PH_METER_PIN A1     
#define THERMOMETER_PIN A2          
#define OXYGEN_METER_PIN A3

//SAMPLE PUMP PARAMETER
#define PUMP_FLOW_SPEED 60 //[ml/min]
#define SAMPLE_SIZE 2 //[ml]
#define PUMP_SAMPLE_TAKING_TIME     int(float(SAMPLE_SIZE)/float(PUMP_FLOW_SPEED)*60*1000) //[ms] //should be 2s (2000ms)

//PH KEEPERS PUMP
#define TIMEBETWENWORK 10000 //[ms] time between ph correction [TODO change name]
#define CORECTIONTIME 100 // [ms] initial time of correction
#define MULTPERDEGRE 3 // it mean if  desire ph is 6 and we have 8 time of pump activate will be 100*3*3 = 900 ms
#define MAXREACTIONTIME 3000




#define THERMISTOR_NOMINAL 10000        // [ohm] resistance at 25 degrees C
#define TEMPERATURE_NOMINAL 25          // temp. for nominal resistance (almost always 25 C)
#define B_COEFFICIENT 3950              // [UNIT!] The beta coefficient of the thermistor (usually 3000-4000)
#define SERIES_RESISTOR 10000           // [ohm] the value of the 'other' resistor     



#endif // BIOREACTOR_CONST