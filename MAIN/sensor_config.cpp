#include "sensor_config.hpp"
#include "eeprom_menager.hpp"
#include <string.h>

Sensor setup_thermometer_sensors(MemoryManager &manager) // setup the sensor
{
    // thermometer
    ConfigurationVariable thermometer_zero_shift(
        manager); // constructor use manager method give_memory and assigns the result to an object memory_addr variable
    thermometer_zero_shift.retrieve_config_values_from_eeprom();
    ConfigurationVariable thermometer_linear(manager);
    thermometer_linear.retrieve_config_values_from_eeprom();
    Thermometer *c_thermometer = new Thermometer(TERMOMETHERPIN);
    Sensor thermometer(c_thermometer, thermometer_zero_shift, thermometer_linear);
    return thermometer;
}

Sensor setup_ph_sensors(MemoryManager &manager) // setup the sensor
{
    // ph-meter
    ConfigurationVariable ph_zero_shift(manager);
    ph_zero_shift.retrieve_config_values_from_eeprom();
    ConfigurationVariable ph_linear(manager);
    ph_linear.retrieve_config_values_from_eeprom();
    PhMeter *c_ph_meter = new PhMeter(PHMETERPIN);
    Sensor ph_meter(c_ph_meter, ph_zero_shift, ph_linear);
    return ph_meter;
}

Sensor setup_oxygen_sensors(MemoryManager &manager) // setup the sensor
{
    // oxygen meter
    ConfigurationVariable oxygen_zero_shift(manager);
    oxygen_zero_shift.retrieve_config_values_from_eeprom();
    ConfigurationVariable oxygen_linear(manager);
    oxygen_linear.retrieve_config_values_from_eeprom();
    OxygenMeter *c_oxygen_meter = new OxygenMeter(OXYGENMETERPIN);
    Sensor oxygen_meter(c_oxygen_meter, oxygen_zero_shift, oxygen_linear);
    return oxygen_meter;
}

void test_sensor(Sensor &sensor, float value_new, String sensor_name = "Sensor")
{
    delay(2000);

    Serial.print("wartosc przesuniecia_zera (po inicjalizacji) dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.zero_shift.return_config_value());

    sensor.zero_shift.retrieve_config_values_from_eeprom();
    delay(20);
    Serial.print("wartosc przesuniecia_zera (po odczytaniu wartosci z eeprom) dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.zero_shift.return_config_value());

    Serial.print("adres w pamieci dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.zero_shift.get_addr());

    sensor.zero_shift.change_config_value(value_new);
    delay(20);
    Serial.print("wartosc przesuniecia_zera (po zmianie na ustawiona wartosc) dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.zero_shift.return_config_value());
    Serial.println("----------------------------------------------------------------------------------------");

    Serial.print("wartosc wspolczynnika linowego (po inicjalizacji) dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.linear_factor.return_config_value());

    sensor.linear_factor.retrieve_config_values_from_eeprom();
    delay(20);
    Serial.print("wartosc wspolczynnika linowego (po odczytaniu wartosci z eeprom) dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.linear_factor.return_config_value());

    Serial.print("adres w pamieci dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.linear_factor.get_addr());

    sensor.linear_factor.change_config_value(value_new);
    delay(20);
    Serial.print("wartosc wspolczynnika linowego (po zmianie na ustawiona wartosc) dla ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.linear_factor.return_config_value());
    Serial.println("-----------------------------------------------------------------------------------------");

    delay(20);

    Serial.print("wartosc odczytana (wprost) z czujnika ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.measuring_device->get_value());

    delay(20);

    Serial.print("wartosc odczytana (po uwzględnieniu wspolczynników) z czujnika ");
    Serial.print(sensor_name);
    Serial.print(": ");
    Serial.println(sensor.get_value());

    Serial.println("-----------------------------------------------------------------------------------------");
    delay(2000);
}
