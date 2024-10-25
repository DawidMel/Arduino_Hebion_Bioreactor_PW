#include <Arduino.h>
#include <unity.h>
#include "eeprom_menager.hpp"


MemoryManager test_manager(0,100);

EepromVariable eeprom_test1(test_manager);
EepromVariable eeprom_test2(test_manager);

void reset_eeprom_variable()
{
    eeprom_test1.change_eeprom_config_value(0.0);
    eeprom_test2.change_eeprom_config_value(0.0);
}

void change_eeprom_to_2137()
{
    eeprom_test1.change_eeprom_config_value(2137.0);
    eeprom_test2.change_eeprom_config_value(2137.0);
}

float retrieve_eeprom_value()
{
    eeprom_test1.retrieve_config_values_from_eeprom();
}


float retrieve_eeprom_value_after_reset()
{
    eeprom_test1.retrieve_config_values_from_eeprom();
}


int get_eeprom_addr()
{
    return eeprom_test2.get_addr();
}


    void test_retrieve_eeprom_value()
    {
    TEST_ASSERT_EQUAL(2137.0,retrieve_eeprom_value());
    }

    void test_get_eeprom_addr()
    {
    TEST_ASSERT_EQUAL(4,get_eeprom_addr());
    }

    void test_retrieve_eeprom_value_after_reset()
    {
        TEST_ASSERT_EQUAL(retrieve_eeprom_value_after_reset, 0.0);
    }

int dumb_func()
{
    return 1;
}

void test_dumb_func()
{
    TEST_ASSERT_EQUAL(1,dumb_func());
}

void setup()
{

UNITY_BEGIN();
// configure eeprom to test
reset_eeprom_variable();
RUN_TEST(test_retrieve_eeprom_value_after_reset);

change_eeprom_to_2137();
RUN_TEST(test_retrieve_eeprom_value);

RUN_TEST(test_get_eeprom_addr);


RUN_TEST(test_dumb_func);

UNITY_END();

}

void loop()
{

}