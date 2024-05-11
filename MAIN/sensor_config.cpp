#include "sensor_config.hpp"
#include "eeprom_menager.hpp"
#include <string.h>

// TODO in free time change "manual" initialization to function

Sensor setup_thermometer_sensors(MemoryManager &manager) // setup the sensor
{
    // thermometer
    ConfigurationVariable thermometer_zero_shift(manager); // constructor use manager method give_memory and assigns the
                                                           // result to an object m_memory_addr variable
    thermometer_zero_shift.retrieve_config_values_from_eeprom();
    ConfigurationVariable thermometer_linear_factor(manager);
    thermometer_linear_factor.retrieve_config_values_from_eeprom();
    Thermometer *measure_dev_thermometer = new Thermometer(TERMOMETHER_PIN);
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

void test_sensor(Sensor &sensor, float value_new, String sensor_name = "Sensor")
{
    delay(1000);

    Serial.print(F("wartosc przesuniecia_zera (po inicjalizacji) dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_zero_shift.return_config_value());

    sensor.m_zero_shift.retrieve_config_values_from_eeprom();
    Serial.print(F("wartosc przesuniecia_zera (po odczytaniu wartosci z eeprom) dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_zero_shift.return_config_value());

    Serial.print(F("adres w pamieci dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_zero_shift.get_addr());

    sensor.m_zero_shift.change_config_value(value_new);
    Serial.print(F("wartosc przesuniecia_zera (po zmianie na ustawiona wartosc) dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_zero_shift.return_config_value());
    Serial.println("----------------------------------------------------------------------------------------");

    Serial.print(F("wartosc wspolczynnika linowego (po inicjalizacji) dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.return_config_value());

    sensor.m_linear_factor.retrieve_config_values_from_eeprom();
    Serial.print(F("wartosc wspolczynnika linowego (po odczytaniu wartosci z eeprom) dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.return_config_value());

    Serial.print(F("adres w pamieci dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.get_addr());

    sensor.m_linear_factor.change_config_value(value_new);
    Serial.print(F("wartosc wspolczynnika linowego (po zmianie na ustawiona wartosc) dla "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_linear_factor.return_config_value());
    Serial.println("-----------------------------------------------------------------------------------------");

    Serial.print(F("wartosc odczytana (wprost) z czujnika "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.m_measuring_device->get_value());

    Serial.print(F("wartosc odczytana (po uwzględnieniu wspolczynników) z czujnika "));
    Serial.print(sensor_name);
    Serial.print(F(": "));
    Serial.println(sensor.get_value());

    Serial.println("-----------------------------------------------------------------------------------------");
    delay(1000);
}
