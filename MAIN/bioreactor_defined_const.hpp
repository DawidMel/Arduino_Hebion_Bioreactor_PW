#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST


#define TERMOMETHERPIN A1
// Thermistor settings   // resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000


#define PHMETERPIN A2
#define OXYGENMETERPIN A3


#define PhSensorPin A0 // pH meter Analog output to Arduino Analog Input 0
#define samplingInterval 20 //Unit!
#define printInterval 800 //Unit!












#endif //BIOREACTOR_CONST