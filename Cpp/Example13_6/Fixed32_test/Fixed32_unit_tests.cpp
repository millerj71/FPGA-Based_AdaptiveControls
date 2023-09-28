#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Fixed32.h"
#include "Fixed32_unit_tests.h"


// Load Values Tests
void runDoubleLoadTest(int32_t NUM_DECIMAL_BITS, int NUM_TESTS, double acceptable_error)
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

void runIntegerLoadTest(int32_t NUM_DECIMAL_BITS, int NUM_TESTS)
{
  bool ALL_TESTS_PASSED = 1;
  Fixed32 test(NUM_DECIMAL_BITS);
  int32_t random_value;
  int32_t error;

  for (int i = 0; i < NUM_TESTS; i++)
  {
    int32_t upper_bits = rand();
    int32_t lower_bits = rand();
    random_value = (upper_bits << 16) | (lower_bits & 0xFFFF);

    test  = random_value;
    error = abs(test.integer - random_value);

    if (error)
    {
      std::cout << "TEST #" << i << " FAILED!! INTEGERS DO NOT MATCH!!! Expected: " << random_value << " | Actual: " << test.integer << std::endl;
      ALL_TESTS_PASSED = 0; 
    }

  }

  if (ALL_TESTS_PASSED) {std::cout << "SUCCESS!!! INTEGER LOADING TEST PASSED!!!" << std::endl;}
}

void runStringLoadTest(int32_t NUM_DECIMAL_BITS, int NUM_TESTS)
{
  bool ALL_TESTS_PASSED = 1;
  Fixed32 test(NUM_DECIMAL_BITS);

  std::string random_value;
  random_value.resize(32);

  for (int i = 0; i < NUM_TESTS; i++)
  {
    // Loading string with random 1s and 0s.
    for (int j = 0; j < 32; j++) {random_value[j] = (rand() % 2 == 1) ? '1' : '0';}

    test = random_value;

    if (test.str_value != random_value)
    {
      std::cout << "TEST #" << i << " FAILED!! STRINGS DO NOT MATCH!!! Expected: " << random_value << " | Actual: " << test.str_value << std::endl;
      ALL_TESTS_PASSED = 0; 
    }
  }

  if (ALL_TESTS_PASSED) {std::cout << "SUCCESS!!! STRING  LOADING TEST PASSED!!!" << std::endl;}
}




// Operation Overrides Tests
void runAddTest(int32_t NUM_DECIMAL_BITS)
{

}

void runSubTest(int32_t NUM_DECIMAL_BITS)
{

}

void runMultTest(int32_t NUM_DECIMAL_BITS)
{

}

void runDivTest(int32_t NUM_DECIMAL_BITS)
{

}