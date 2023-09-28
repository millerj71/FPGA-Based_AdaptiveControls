
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Fixed32.h"

// Loading Values Tests
void runDoubleLoadTest( int32_t NUM_DECIMAL_BITS, int NUM_TESTS = 100, double acceptable_error = 0.000001);
void runIntegerLoadTest(int32_t NUM_DECIMAL_BITS, int NUM_TESTS = 100);
void runStringLoadTest( int32_t NUM_DECIMAL_BITS, int NUM_TESTS = 100);

// Operation Overrides Tests
void runAddTest(int32_t NUM_DECIMAL_BITS);
void runSubTest(int32_t NUM_DECIMAL_BITS);
void runMultTest(int32_t NUM_DECIMAL_BITS);
void runDivTest(int32_t NUM_DECIMAL_BITS);