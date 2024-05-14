#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST


//BUTTON SETTING
#define BUTTONDEFAULTSTATE 1 //mean pin state is HIGH
#define BUTTONSTAYONSTATE 1500 //[ms] time button dont change its state
#define STAYINMENUTIME 3000 //[ms] time after you can exit menu


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
#define CSPIN 10
#define MOSIPIN 11
#define MISOPIN 12
#define SCKPIN 13
#define FILENAME "m.txt"

//ROTARY ENCODER PHYSICAL CONNECTION
#define REPINA 3
#define REPINB 4
#define REBUTTONPIN 5

//SENSORS PHYSICAL CONNECTION


#define THERMOMETHERPIN A1              // Thermistor settings   
#define THERMISTOR_NOMINAL 10000        // [ohm] resistance at 25 degrees C
#define TEMPERATURE_NOMINAL 25          // temp. for nominal resistance (almost always 25 C)
#define B_COEFFICIENT 3950              // [UNIT!] The beta coefficient of the thermistor (usually 3000-4000)
#define SERIES_RESISTOR 10000           // [ohm] the value of the 'other' resistor     


#define PH_METER_PIN A0      // pH meter Analog output to Arduino Analog Input 0
#define THERMOMETER_METER_PIN A2
#define OXYGEN_METER_PIN A3


#define SAMPLING_INTERVAL 20 // [UNIT!]
#define PRINT_INTERVAL 800   // [UNIT!]

#endif // BIOREACTOR_CONST