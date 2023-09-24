
#include <cmath>
#include <cstdio>
#include <string>

#include "Fixed32.h"

// Constructor
Fixed32::Fixed32() {}
Fixed32::Fixed32(int num_dec)
{
  NUM_DECIMAL_BITS = num_dec;
  NUM_WHOLE_BITS   = NUM_VALUE_BITS - NUM_DECIMAL_BITS;
}

Fixed32::~Fixed32() {}



// Update Value Representations
void Fixed32::updateValueRepresentations(const Fixed32& rhs)
{
  updateBinaryRepresentation(rhs);
  updateStringRepresentation();
  updateDoubleRepresentation();
  updateIntegerRepresentation();
}

void Fixed32::updateValueRepresentations(const double& rhs)
{
  updateBinaryRepresentation(rhs);
  updateStringRepresentation();
  updateDoubleRepresentation();
  updateIntegerRepresentation();
}

void Fixed32::updateValueRepresentations(const int32_t& rhs)
{
  updateBinaryRepresentation(rhs);
  updateStringRepresentation();
  updateDoubleRepresentation();
  updateIntegerRepresentation();
}

void Fixed32::updateValueRepresentations(const std::string& rhs)
{
  updateBinaryRepresentation(rhs);
  updateStringRepresentation();
  updateDoubleRepresentation();
  updateIntegerRepresentation();
}




// Update Binary Representations
void Fixed32::updateBinaryRepresentation(const Fixed32& rhs)
{
  for (int i = 0; i < NUM_BITS; i++)
  {
    binary[i] = rhs.binary[i];
    binary_mag[i] = rhs.binary_mag[i];
  }

  isNegative = rhs.isNegative;
}

void Fixed32::updateBinaryRepresentation(const double& rhs)
{
  double RHS = rhs;
  isNegative = 0;
  if (RHS < 0) 
  { 
    isNegative = 1;
    RHS = (-1)*RHS;
  }

  for (int i = 0; i < NUM_VALUE_BITS; i++)
  {
    binary[NUM_VALUE_BITS-1 - i] = 0;

    if (RHS > pow(2, NUM_WHOLE_BITS - i))
    {
      RHS = RHS - pow(2, NUM_WHOLE_BITS - i);
      binary[NUM_VALUE_BITS-1 - i] = 1;
    }
    
  }

  binary[SIGN_BIT] = 0;

  for (int i = 0; i < NUM_BITS; i++)
  {
    binary_mag[i] = binary[i];
  }

  if (isNegative)
  {
    applyTwosCompliment();
  }
}

void Fixed32::updateBinaryRepresentation(const int32_t& rhs)
{
  int32_t number = rhs;

  if (number < 0)
  {
    isNegative = 1;
    number = (-1)*number;
  }

  for (int i = NUM_VALUE_BITS-1 ; i >= 0; i--)
  {
    binary[i] = 0;

    if (number >= pow(2, i))
    {
      number = number - pow(2,i);
      binary[i] = 1;
    }
  }

  binary_mag[SIGN_BIT] = 0;

  for (int i = 0; i < NUM_BITS; i++)
  {
    binary_mag[i] = binary[i];
  }

  if (isNegative)
  {
    applyTwosCompliment();
  }
}

void Fixed32::updateBinaryRepresentation(const std::string& rhs)
{
  if (rhs.length() != NUM_BITS)
  {
    return;
  }

  for (int i = 0; i < NUM_BITS; i++)
  {
    binary[NUM_BITS-1 - i] = 0;

    if (rhs[i] == '1')
    {
      binary[NUM_BITS-1 - i] = 1;
    }
  }

  isNegative = 0;
  if (binary[NUM_BITS-1])
  {
    isNegative = 1;
  }

  if (isNegative)
  {
    applyTwosCompliment();
    for (int i = 0; i < NUM_BITS; i++)
    {
      binary_mag[i] = binary[i];
    }
    applyTwosCompliment();
  }

}




// Update Other Representations
void Fixed32::updateStringRepresentation()
{
  std::string update;
  update.resize(NUM_BITS);

  for (int i = 0; i < NUM_BITS; i++)
  {
    update[i] = '0';
    if (binary[NUM_BITS-1 - i]) {update[i] = '1';}
  }

  str_value = update;
}

void Fixed32::updateDoubleRepresentation()
{
  double update = 0;
  for (int i = 0; i < NUM_BITS; i++)
  {
    if (binary_mag[i]) 
    {
      update = update + pow(2, i+1 - NUM_DECIMAL_BITS); 
    }
  }

  if (isNegative)
  {
    update = (-1)*update;
  }

  double_value = update;
}

void Fixed32::updateIntegerRepresentation()
{
  int32_t update = 0;
  for (int i = 0; i < NUM_VALUE_BITS; i++)
  {
    // The integer value represents how the binary would be interpretted 
    // if it were an integer instead of a fixed point decimal. 
    if (binary_mag[i]) 
    {
      update = update + pow(2, i);
    }
  }

  if (isNegative)
  {
    update = (-1)*update;
  }

  integer = update;
}




// Print Functions for Testing
void Fixed32::print()
{
  printBinary();
  printString();
  printDouble();
  printInteger();
  printIntegerBinary();
}

void Fixed32::printBinary()
{
  std::cout << "binary = ";
  for (int i = 0 ; i < NUM_BITS ; i++)
  {
    std::cout << binary[NUM_BITS-1 - i];
  }
  std::cout << std::endl;
}

void Fixed32::printString()
{
  std::cout << "string = " << str_value << std::endl;
}

void Fixed32::printDouble()
{
  std::cout << "double = " << double_value << std::endl;
}

void Fixed32::printInteger()
{
  std::cout << "integer = " << integer << std::endl;
}

void Fixed32::printIntegerBinary()
{
  int number = integer;
  int total_bits = sizeof(integer) * 8;

  std::cout << "integer-binary = ";
  for (int i = total_bits-1; i >= 0; --i)
  {
    int bit = (number & (1 << i)) ? 1 : 0;
    std::cout << bit;
  }
  std::cout << std::endl;
}




// Overloading = Operator
Fixed32& Fixed32::operator=(const Fixed32& rhs)
{
  updateValueRepresentations(rhs);
  return *this;
}

Fixed32& Fixed32::operator=(const double& rhs)
{
  updateValueRepresentations(rhs);
  return *this;
}

Fixed32& Fixed32::operator=(const int32_t& rhs)
{
  updateValueRepresentations(rhs);
  return *this;
}

Fixed32& Fixed32::operator=(const std::string& rhs)
{
  updateValueRepresentations(rhs);
  return *this;
}




void Fixed32::applyTwosCompliment()
{
  int32_t  update;
  uint32_t current;

  current = toUnsignedInteger();
  update  = (-1)*current;
  toBinary(update);

}

uint32_t Fixed32::toUnsignedInteger()
{
  uint32_t output = 0;
  for (int i = 0; i < NUM_BITS; i++)
  {
    if (binary[i])
    {
      output = output + pow(2, i);
    }
  }

  return output;
}

void Fixed32::toBinary(int32_t input)
{
  int number = input;
  int total_bits = sizeof(input) * 8;

  for (int i = total_bits-1; i >= 0; --i)
  {
    int bit = (number & (1 << i)) ? 1 : 0;

    if (bit) {binary[i] = 1;}
    else {binary[i] = 0;}
  }
}




// Overloading + Operator
Fixed32 operator+(const Fixed32& a, const Fixed32& b)
{
  Fixed32 output(a.NUM_DECIMAL_BITS);
  output = a.integer + b.integer;
  return output;
}

Fixed32 operator+(const Fixed32& a, const double& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a + B;
}

Fixed32 operator+(const double& a, const Fixed32& b)
{
  Fixed32 output(b.NUM_DECIMAL_BITS);
  output = b + a;
  return output;
}