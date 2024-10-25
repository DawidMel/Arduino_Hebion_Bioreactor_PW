#include <Arduino.h>
#include <unity.h>
#include "eeprom_menager.hpp"



//test 1

int dumb_func()
{
    return 1;
}

void test_dumb_func()
{
    TEST_ASSERT_EQUAL(1,dumb_func());
}


//setup for test 2-4

MemoryManager test_manager(0,100);

EepromVariable eeprom_test1(test_manager);
EepromVariable eeprom_test2(test_manager);


void reset_eeprom_variable()
{
    eeprom_test1.change_eeprom_config_value(0.0);
    delay(10);
    eeprom_test2.change_eeprom_config_value(0.0);
    delay(10);
}

void change_eeprom_to_2137()
{
    eeprom_test1.change_eeprom_config_value(2137.0);
    delay(10);
    eeprom_test2.change_eeprom_config_value(2137.0);
    delay(10);
}

float retrieve_eeprom_value()
{
    float temp;
    temp = eeprom_test1.retrieve_config_values_from_eeprom();
    Serial.println(temp);
    return temp;
}



//test 2  FOR SOME REASON CODE WORK FINE BUT TEST DONT WORK RIGHT


void test_retrieve_eeprom_value_after_reset()
{
    TEST_ASSERT_EQUAL(0.0, retrieve_eeprom_value());
}

//test 3



void test_retrieve_eeprom_value()
{
TEST_ASSERT_EQUAL(2137.0,retrieve_eeprom_value());
}



//test 4

int get_eeprom_addr()
{
    return eeprom_test2.get_addr();
}


void test_get_eeprom_addr()
{
TEST_ASSERT_EQUAL(4,get_eeprom_addr());
}




void setup()
{

Serial.begin(9600);

UNITY_BEGIN();
// configure eeprom to test

delay(10);
RUN_TEST(test_dumb_func);


delay(10);
Serial.println(eeprom_test1.retrieve_config_values_from_eeprom());
reset_eeprom_variable();
Serial.println(eeprom_test1.retrieve_config_values_from_eeprom());
delay(10);
Serial.println(eeprom_test1.retrieve_config_values_from_eeprom());
RUN_TEST(test_retrieve_eeprom_value_after_reset);
Serial.println(eeprom_test1.retrieve_config_values_from_eeprom());

delay(10);
change_eeprom_to_2137();

delay(10);
RUN_TEST(test_retrieve_eeprom_value);

delay(10);
RUN_TEST(test_get_eeprom_addr);




UNITY_END();

}

void loop()
{

}