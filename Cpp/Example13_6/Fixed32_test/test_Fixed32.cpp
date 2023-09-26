
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Fixed32.h"
#include "Fixed32_unit_tests.h"



int main()
{

  int32_t NUM_DECIMAL_BITS = 24;

  runDoubleLoadTest(NUM_DECIMAL_BITS);
  runIntegerLoadTest(NUM_DECIMAL_BITS);
  runStringLoadTest(NUM_DECIMAL_BITS);


  Fixed32 test(NUM_DECIMAL_BITS);
  double mult1 = 12.34;
  double mult2 = -2.34;
  test = mult2;
  Fixed32 test2(NUM_DECIMAL_BITS);
  test2 = test * mult1;

  std::cout << "Test1:" << std::endl;
  test.print();
  std::cout << std::endl << "Test2:" << std::endl;
  test2.print();

  Fixed32 test3(NUM_DECIMAL_BITS);
  test3 = mult1 * mult2;
  std::cout << std::endl << "Test3:" << std::endl;
  test3.print();

  return 0;
}


