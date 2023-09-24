
#include <iostream>
#include <string>
#include "Fixed32.h"


int main()
{

  // std:: cout << "Hello World!" << std::endl;
  Fixed32 test(25);

  // Double Load Test
  double load_val = -124.34;
  test = load_val;

  // Integer Load Test
  // int32_t int_val = -65189969;
  // test = int_val;

  // // String Load Test
  // std::string string_val = "10000011101010001111010111000011";
  // test = string_val;


  std::cout << "Test:" << std::endl;
  test.print();
  std::cout << std::endl;

  std::cout << "Test2:" << std::endl;
  double increment_value = 1.2345;
  // int32_t increment_value = 1879048191;
  Fixed32 test2(25);
  // test2 = test + test;
  test2 = test + increment_value;


  test2.print();

  return 0;
}
