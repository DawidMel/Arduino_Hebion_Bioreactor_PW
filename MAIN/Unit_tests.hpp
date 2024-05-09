#include <AUnit.h>
#include "utility.hpp"

#ifndef MY_UNIT_TEST
#define MY_UNIT_TEST

int dumb_func() {return 1;}


measure_arr m1(10),m2(3);  //10 ; 3


float test_mes_arry(measure_arr& ma)
{
  ma.add_measure(20);
  ma.add_measure(10);
  ma.add_measure(5);
  ma.add_measure(5);
  ma.add_measure(60);
  return (ma.get_average());
}

float test_mes_arry2(measure_arr& ma)
{
  ma.add_measure(20);
  ma.add_measure(10);
  ma.add_measure(2137);

  return ma.read_mesure(2); 
}


test(test_mes_arryTest)
{
  assertEqual(test_mes_arry(m1),10.0);
}

test(test_mes_arry2Test)
{
  assertEqual(test_mes_arry2(m2),2137.0);
}



test(dumb_funcTest)
{
  assertEqual(dumb_func(), 1);
}




#endif //MY_UNIT_TEST