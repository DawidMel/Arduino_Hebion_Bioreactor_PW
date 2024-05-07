#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST


#define THERMISTORPIN A1

// Analog read samples
#define NUMSAMPLES 10

// Thermistor settings   // resistance at 25 degrees C
#define THERMISTORNOMINAL 10000

// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer  // but is more 'smooth'
#define NUMSAMPLES 5

// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950


// the value of the 'other' resistor
#define SERIESRESISTOR 10000


#define PhSensorPin A0 // pH meter Analog output to Arduino Analog Input 0

#define samplingInterval 20 //Unit!
#define printInterval 800 //Unit!
#define ArrayLenth 40  //Unit!





#endif //BIOREACTOR_CONST