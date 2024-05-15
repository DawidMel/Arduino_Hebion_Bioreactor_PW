#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST


//BUTTON SETTING
#define BUTTONDEFAULTSTATE 1 //mean pin state is HIGH
#define BUTTONSTAYONSTATE 2000 //[ms] time button dont change its state
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
#define PH_METER_PIN A1     
#define THERMOMETHERPIN A2          
#define OXYGEN_METER_PIN A3

//SAMPLE PUMP PARAMETER
#define PUMPFLOWSPEED 60 //[ml/min]
#define SAMPLESIZE 2 //[ml]
#define PUMPSAMPLETAKINGTIME     int(float(SAMPLESIZE)/float(PUMPFLOWSPEED)*60*1000) //[ms] //powinno wyjsc 2 sekundy

//PH KEEPERS PUMP
#define TIMEBETWENWORK 10000 //[ms] time between ph correction
#define CORECTIONTIME 100 // [ms] initial time of corection
#define MULTPERDEGRE 3 // it mean if  desire ph is 6 and we have 8 time of pump activate will be 100*3*3 = 900 ms
#define MAXREACTIONTIME 5000




#define THERMISTOR_NOMINAL 10000        // [ohm] resistance at 25 degrees C
#define TEMPERATURE_NOMINAL 25          // temp. for nominal resistance (almost always 25 C)
#define B_COEFFICIENT 3950              // [UNIT!] The beta coefficient of the thermistor (usually 3000-4000)
#define SERIES_RESISTOR 10000           // [ohm] the value of the 'other' resistor     



#endif // BIOREACTOR_CONST