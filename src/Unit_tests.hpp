#include <AUnit.h>
#include "utility.hpp"
#include "eeprom_menager.hpp"

#ifndef MY_UNIT_TEST
#define MY_UNIT_TEST

// not refactored

MeasureArray m1(10), m2(3); // 10 ; 3

float test_mes_array(MeasureArray &ma)
{
    ma.add_measure(20);
    ma.add_measure(10);
    ma.add_measure(5);
    ma.add_measure(5);
    ma.add_measure(60);
    return (ma.get_average());
}

test(test_mes_arrayTest)
{
    assertEqual(test_mes_array(m1), 10.0);
}


float test_mes_array2(MeasureArray &ma)
{
    ma.add_measure(20);
    ma.add_measure(10);
    ma.add_measure(2137);

    return ma.read_measure(2);
}


test(test_mes_array2Test)
{
    assertEqual(test_mes_array2(m2), 2137.0);
}

//test eeprom  REQUIRE 2 RUN OF THE TEST



#endif // MY_UNIT_TEST