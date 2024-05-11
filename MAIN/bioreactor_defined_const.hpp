#ifndef BIOREACTOR_CONST
#define BIOREACTOR_CONST



#define MOSIPIN 11
#define MISOPIN 12
#define SCKPIN 13
#define FILENAME "measurement.txt"



#define TERMOMETHER_PIN A1
// Thermistor settings   // resistance at 25 degrees C
#define THERMISTOR_NOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURE_NOMINAL 25
// The beta coefficient of the thermistor (usually 3000-4000)
#define B_COEFFICIENT 3950
// the value of the 'other' resistor
#define SERIES_RESISTOR 10000

#define PH_METER_PIN A2
#define OXYGEN_METER_PIN A3

#define PH_METER_PIN A0      // pH meter Analog output to Arduino Analog Input 0
#define SAMPLING_INTERVAL 20 // Unit!
#define PRINT_INTERVAL 800   // Unit!

#endif // BIOREACTOR_CONST