#include <AUnit.h>
#include "utility.hpp"

#ifndef MY_UNIT_TEST
#define MY_UNIT_TEST

int dumb_func() {return 1;}


mesure_arr m1(10),m2(3);


float test_mes_arry(mesure_arr& ma)
{
  ma.add_mesure(20);
  ma.add_mesure(10);
  ma.add_mesure(5);
  ma.add_mesure(5);
  ma.add_mesure(60);
  return (ma.get_average());
}

float test_mes_arry2(mesure_arr& ma)
{
  ma.add_mesure(20);
  ma.add_mesure(10);
  ma.add_mesure(2137);

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