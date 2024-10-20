#include "sensor_config.hpp"
#include "eeprom_menager.hpp"
#include <string.h>

// TODO in free time change "manual" initialization to function

const char* SEPARATING_LINE = "----------------------------------------------------------------------------------------";

Sensor setup_thermometer_sensors(MemoryManager &manager) // setup the sensor
{
    // thermometer
    ConfigurationVariable thermometer_zero_shift(manager); // constructor use manager method give_memory and assigns the
                                                           // result to an object m_memory_addr variable
    thermometer_zero_shift.retrieve_config_values_from_eeprom();
    ConfigurationVariable thermometer_linear_factor(manager);
    thermometer_linear_factor.retrieve_config_values_from_eeprom();
    Thermometer *measure_dev_thermometer = new Thermometer(THERMOMETER_PIN);
    Sensor thermometer(measure_dev_thermometer, thermometer_zero_shift, thermometer_linear_factor);
    return thermometer;
}

//TODO: Change to template
Sensor setup_ph_sensors(MemoryManager &manager) // setup the sensor
{
    // ph-meter
    ConfigurationVariable ph_zero_shift(manager);
    ph_zero_shift.retrieve_config_values_from_eeprom();
    ConfigurationVariable ph_linear_factor(manager);
    ph_linear_factor.retrieve_config_values_from_eeprom();
    PhMeter *measure_dev_ph_meter = new PhMeter(PH_METER_PIN);
    Sensor ph_meter(measure_dev_ph_meter, ph_zero_shift, ph_linear_factor);
    return ph_meter;
}

Sensor setup_oxygen_sensors(MemoryManager &manager) // setup the sensor
{
    // oxygen meter
    ConfigurationVariable oxygen_zero_shift(manager);
    oxygen_zero_shift.retrieve_config_values_from_eeprom();
    ConfigurationVariable oxygen_linear_factor(manager);
    oxygen_linear_factor.retrieve_config_values_from_eeprom();
    OxygenMeter *measure_dev_oxygen_meter = new OxygenMeter(OXYGEN_METER_PIN);
    Sensor oxygen_meter(measure_dev_oxygen_meter, oxygen_zero_shift, oxygen_linear_factor);
    return oxygen_meter;
}

void test_sensor(Sensor &sensor, float value_new, String sensor_name = "Sensor")  //TODO [Check if this sentence make sense]
{
    delay(1000);

    Serial.print(sensor_name);
    Serial.print(F(" zero shift value (after initialization)"));
    Serial.print(F(": "));
    Serial.println(sensor.m_zero_shift.return_config_value());

    sensor.m_zero_shift.retrieve_config_values_from_eeprom();

    Serial.print(sensor_name);
    Serial.print(F(" zero shift value (after read value from eeprom)"));
    Serial.print(F(": "));
    Serial.println(sensor.m_zero_shift.return_config_value());

    Serial.print(sensor_name);
    Serial.print(F(" memory address"));
    Serial.print(F(": "));
    Serial.println(sensor.m_zero_shift.get_addr());

    sensor.m_zero_shift.change_config_value(value_new);

    Serial.print(sensor_name);
    Serial.print(F(" Zero shift value (after changing to the set value)"));
    Serial.print(F(": ")); 
    Serial.println(sensor.m_zero_shift.return_config_value());
    Serial.println(SEPARATING_LINE); 

    Serial.print(sensor_name);
    Serial.print(F(" value of the linear coefficient (after initialization)"));
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.return_config_value());

    sensor.m_linear_factor.retrieve_config_values_from_eeprom();

    Serial.print(sensor_name);
    Serial.print(F(" value of the linear coefficient (after read value from eeprom)"));
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.return_config_value());

    Serial.print(sensor_name);
    Serial.print(F(" memory address"));
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.get_addr());

    sensor.m_linear_factor.change_config_value(value_new);

    Serial.print(sensor_name);
    Serial.print(F(" value of the linear coefficient (after changing to the set value)"));
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.return_config_value());
    Serial.println(SEPARATING_LINE);

    Serial.print(F("read value (directly) from "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_measuring_device->get_value());

    Serial.print(F("read value (after taking into account the calibration coefficients set) from ")); //TODO check i it is right term
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.get_value_from_measurement());

    Serial.println(SEPARATING_LINE);
    delay(1000);
}
