#include "utility.hpp"
#include <AUnit.h>

#ifndef MY_UNIT_TEST
#define MY_UNIT_TEST

// not refactored

int dumb_func()
{
    return 1;
}

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

float test_mes_array2(MeasureArray &ma)
{
    ma.add_measure(20);
    ma.add_measure(10);
    ma.add_measure(2137);

    return ma.read_measure(2);
}

test(test_mes_arrayTest)
{
    assertEqual(test_mes_array(m1), 10.0);
}

test(test_mes_array2Test)
{
    assertEqual(test_mes_array2(m2), 2137.0);
}

test(dumb_funcTest)
{
    assertEqual(dumb_func(), 1);
}

#endif // MY_UNIT_TEST