
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Fixed32.h"
#include "Fixed32_unit_tests.h"


// TODO: Error Checking in case an operation is preformed using 
// two Fixed32 variables with different NUM_DECIMAL_BITS. At least
// until I update the code to account for that case.  


int main()
{

  int32_t NUM_DECIMAL_BITS = 25;

  runDoubleLoadTest(NUM_DECIMAL_BITS);
  runIntegerLoadTest(NUM_DECIMAL_BITS);
  runStringLoadTest(NUM_DECIMAL_BITS);


  int32_t int1  = 89590333;
  double  dub1 = 5.34;
  std::string str1 = "00000101010101110000101000111101";

  int32_t int2  = -39258685;
  double  dub2 = -2.34;
  std::string str2 = "11111101101010001111010111000011";

  Fixed32 test1(NUM_DECIMAL_BITS);
  test1 = str1;

  Fixed32 test2(NUM_DECIMAL_BITS);
  test2 = str2;

  Fixed32 test3(NUM_DECIMAL_BITS);
  test3 = str1 * test2;

  Fixed32 test4(NUM_DECIMAL_BITS);
  test4 = dub1 * dub2;

  // std::cout << "Test1:" << std::endl;
  // test1.print();

  // std::cout << std::endl << "Test2:" << std::endl;
  // test2.print();

  // std::cout << std::endl << "Test3:" << std::endl;
  // test3.print();

  // std::cout << std::endl << "Test4:" << std::endl;
  // test4.print();

  // std::cout << std::endl << "---------------------------------------------------" << std::endl;
  // std::cout << "Test3.double = " << test3.double_value << " | Test4.double = " << test4.double_value << std::endl;
  // std::cout << "---------------------------------------------------" << std::endl << std::endl;


  // Fixed32 test5(NUM_DECIMAL_BITS);
  // test5 = "00000010101000110000001000110001";
  // test5.print();
// XXXXXXXXXXXXXXXXXXXXXXX00000010101000110000001000110000XXXXXXXXX
// 0000000000000000000000000000010101000110000001000110001011100111
// 00000000000000000000000000000101010001100000010001100010

  return 0;
}


