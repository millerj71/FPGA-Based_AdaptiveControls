
#include <cmath>
#include <cstdio>
#include <string>
#include <bitset>

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

  for (int i = 0; i < NUM_BITS; i++)
  {
    binary[NUM_BITS-1 - i] = 0;

    if (RHS > pow(2, NUM_WHOLE_BITS + 1 - i))
    {
      RHS = RHS - pow(2, NUM_WHOLE_BITS + 1 - i);
      binary[NUM_BITS-1 - i] = 1;
    }
    
  }

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
  std::bitset<32> rhs_bits(rhs);
  std::bitset<32> mag_bits(abs(rhs));

  for (int i = 0; i < NUM_BITS; i++)
  {
    binary[i]     = (rhs_bits[i] == 1) ? 1 : 0;
    binary_mag[i] = (mag_bits[i] == 1) ? 1 : 0;
  }

  isNegative = (rhs < 0) ? 1 : 0;

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
  else
  {
    for (int i = 0; i < NUM_BITS; i++)
    {
      binary_mag[i] = binary[i];
    }
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
  int32_t result = 0;
  for(int i = 0; i < NUM_BITS; ++i) {
      if(binary_mag[NUM_BITS-1 - i]) {
          // Using the OR operator to set the appropriate bit
          // if the corresponding bool value is true.
          result |= (1 << (31 - i));
      }
  }

  if (isNegative)
  {
    result = -result;
  }
  integer = result;

  int number = integer;
  int total_bits = sizeof(integer) * 8;

  for (int i = total_bits-1; i >= 0; --i)
  {
    integer_binary[i] = (number & (1 << i)) ? 1 : 0;
  }

}


void Fixed32::applyTwosCompliment()
{

  bool neg_bin[32];
  bool one[32];

  for (int i = 0; i < NUM_BITS; i++)
  {
    neg_bin[i] = !binary[i];
    one[i]    = 0;
  }
  one[0] = 1;

  bool carry = 0;
  bool update[32];
  for (int i = 0; i < NUM_BITS; i++)
  {
    update[i] = neg_bin[i] ^ one[i] ^ carry;
    carry = (neg_bin[i] & one[i]) | (carry & (neg_bin[i] ^ one[i]));
  }

  for (int i = 0; i < NUM_BITS; i++)
  {
    binary[i] = update[i];
  }
  
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
  std::cout << "integer-binary = ";
  for (int i = 0 ; i < NUM_BITS ; i++)
  {
    std::cout << integer_binary[NUM_BITS-1 - i];
  }
  std::cout << std::endl;
}
