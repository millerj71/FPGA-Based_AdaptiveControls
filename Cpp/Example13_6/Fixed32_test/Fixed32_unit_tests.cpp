#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Fixed32.h"
#include "Fixed32_unit_tests.h"


// Load Values Tests
void runDoubleLoadTest(int32_t NUM_DECIMAL_BITS, double acceptable_error, int NUM_TESTS)
{
  bool ALL_TESTS_PASSED = 1;
  Fixed32 test(NUM_DECIMAL_BITS);
  double random_value;
  double error;
  double offset = 16.0;

  for (int i = 0; i < NUM_TESTS; i++)
  {
    random_value = (rand() / 1000.0) - offset;  // Offset random value to test negative values
    test  = random_value;
    error = fabs(test.double_value - random_value);

    if (error > acceptable_error)
    {
      std::cout << "TEST #" << i << " FAILED!! DOUBLES DO NOT MATCH!!! Expected: " << random_value << " | Actual: " << test.double_value << std::endl;
      ALL_TESTS_PASSED = 0;
    }

  }

  if (ALL_TESTS_PASSED) {std::cout << "SUCCESS!!! DOUBLE  LOADING TEST PASSED!!!" << std::endl;}
}

// void runIntegerLoadTest(int32_t NUM_DECIMAL_BITS)
// {
//   int NUM_TESTS = 100;

//   bool bins_match = 1;
//   bool strings_match = 1;
//   bool integers_match = 1;
//   bool ALL_TESTS_PASSED = 1;

//   for (int i = 0; i < NUM_TESTS; i++)
//   {
    
//     int32_t upper_bits = rand();
//     int32_t lower_bits = rand();
//     int32_t random_value = (upper_bits << 16) | (lower_bits & 0xFFFF);

//     Fixed32 test(NUM_DECIMAL_BITS);
//     test = random_value;


//     for (int j = 0; j < 32; j++)
//     {
//       if (test.binary[j] != test.integer_binary[j])
//       {
//         bins_match = 0;
//       }

//       if (test.binary[j] == 1 && test.str_value[31 - j] == '0')
//       {
//         strings_match = 0;
//       }

//     }

//     if (!bins_match)
//     {
//       std::cout << "TEST #" << i << " FAILED!! BINARIES DO NOT MATCH!!!" << std::endl;
//       test.print();
//       bins_match = 1;
//       ALL_TESTS_PASSED = 0;
//     }

//     if (!strings_match)
//     {
//       std::cout << "TEST #" << i << " FAILED!! STRINGS DO NOT MATCH!!!" << std::endl;
//       test.print();
//       strings_match = 1;
//       ALL_TESTS_PASSED = 0;
//     }

//     if (test.integer != random_value)
//     {
//       std::cout << "TEST #" << i << " FAILED!! INPUT AND OUTPUT DO NOT MATCH!!!" << std::endl;
//       test.print();
//       ALL_TESTS_PASSED = 0;
//     }

//   }

//   if (ALL_TESTS_PASSED)
//   {
//     std::cout << "SUCCESS!!! INTEGER LOADING TEST PASSED!!!" << std::endl;
//   }
// }

// void runStringLoadTest(int32_t NUM_DECIMAL_BITS)
// {
//   int NUM_TESTS = 100;

//   bool bins_match = 1;
//   bool strings_match = 1;
//   bool integers_match = 1;
//   bool ALL_TESTS_PASSED = 1;

//   for (int i = 0; i < NUM_TESTS; i++)
//   {
    
//     int32_t upper_bits = rand();
//     int32_t lower_bits = rand();
//     int32_t random_value = (upper_bits << 16) | (lower_bits & 0xFFFF);

//     Fixed32 pretest(NUM_DECIMAL_BITS);
//     pretest = random_value;

//     std::string random_string;
//     random_string = pretest.str_value;
//     Fixed32 test(NUM_DECIMAL_BITS);
//     test = random_string;

//     for (int j = 0; j < 32; j++)
//     {
//       if (test.binary[j] != test.integer_binary[j])
//       {
//         bins_match = 0;
//       }

//       if (test.binary[j] == 1 && test.str_value[31 - j] == '0')
//       {
//         strings_match = 0;
//       }

//     }

//     if (!bins_match)
//     {
//       std::cout << "TEST #" << i << " FAILED!! BINARIES DO NOT MATCH!!!" << std::endl;
//       test.print();
//       bins_match = 1;
//       ALL_TESTS_PASSED = 0;
//     }

//     if (!strings_match)
//     {
//       std::cout << "TEST #" << i << " FAILED!! STRINGS DO NOT MATCH!!!" << std::endl;
//       test.print();
//       strings_match = 1;
//       ALL_TESTS_PASSED = 0;
//     }

//     if (test.str_value != random_string)
//     {
//       std::cout << "TEST #" << i << " FAILED!! INPUT AND OUTPUT DO NOT MATCH!!!" << std::endl;
//       test.print();
//       ALL_TESTS_PASSED = 0;
//     }

//   }

//   if (ALL_TESTS_PASSED)
//   {
//     std::cout << "SUCCESS!!! STRING  LOADING TEST PASSED!!!" << std::endl;
//   }

// }


// // Operation Overrides Tests
// void runAddTest(int32_t NUM_DECIMAL_BITS)
// {

// }

// void runSubTest(int32_t NUM_DECIMAL_BITS)
// {

// }

// void runMultTest(int32_t NUM_DECIMAL_BITS)
// {

// }

// void runDivTest(int32_t NUM_DECIMAL_BITS)
// {

// }