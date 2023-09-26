
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



void Fixed32::updateValueRepresentations(const Fixed32& rhs)
{
  updateBinaryRepresentation(rhs);
  updateRemainingRepresentations();
}

void Fixed32::updateValueRepresentations(const double& rhs)
{
  updateBinaryRepresentation(rhs);
  updateRemainingRepresentations();
}

void Fixed32::updateValueRepresentations(const int32_t& rhs)
{
  updateBinaryRepresentation(rhs);
  updateRemainingRepresentations();
}

void Fixed32::updateValueRepresentations(const std::string& rhs)
{
  updateBinaryRepresentation(rhs);
  updateRemainingRepresentations();
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
  isNegative = (rhs < 0) ? 1 : 0;
  double RHS = (rhs < 0) ? -rhs : rhs;
  double exp, decr;
  for (int i = 0; i < NUM_BITS; i++)
  {
    exp  = pow(2, NUM_WHOLE_BITS+1 - i);
    decr = (RHS > exp) ? exp : 0;
    RHS  = RHS - decr;

    binary[NUM_BITS-1 - i]  = (decr != 0) ? 1 : 0;
    binary_mag[NUM_BITS-1 - i] = binary[NUM_BITS-1 - i];
  }

  if (isNegative) { applyTwosCompliment(); }

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
  if (rhs.length() != NUM_BITS) { return; }

  std::bitset<32> bits(rhs);

  int32_t num = static_cast<int32_t>(bits.to_ulong());
  std::bitset<32> mag_bits(abs(num));

  for (int i = 0; i < NUM_BITS; i++)
  {
    binary[i]     = (bits[i] == 1)     ? 1 : 0;
    binary_mag[i] = (mag_bits[i] == 1) ? 1 : 0;
  }

  isNegative = (binary[NUM_BITS-1]) ? 1 : 0;
}




// Update Other Representations
void Fixed32::updateRemainingRepresentations()
{
  updateStringRepresentation();
  updateDoubleRepresentation();
  updateIntegerRepresentation();
  updateIntegerBinaryRepresentation();  
}

void Fixed32::updateStringRepresentation()
{
  str_value.resize(NUM_BITS);

  for (int i = 0; i < NUM_BITS; i++)
  {
    str_value[i] = (binary[NUM_BITS-1 - i]) ? '1' : '0';
  }
}

void Fixed32::updateDoubleRepresentation()
{
  double update = 0;
  double incr;
  for (int i = 0; i < NUM_BITS; i++)
  {
    incr    = (binary_mag[i]) ? pow(2, i+1 - NUM_DECIMAL_BITS) : 0;
    update  = update + incr;
  }

  double_value = (isNegative) ? -update : update;
}

void Fixed32::updateIntegerRepresentation()
{
  std::bitset<32> bits;
  for (int i = 0; i < NUM_BITS; i++)
  {
    bits[i] = (binary[i]) ? 1 : 0;
  }

  integer = static_cast<int32_t>(bits.to_ulong());
}

void Fixed32::updateIntegerBinaryRepresentation()
{
  std::bitset<32> int_bits(integer);
  for (int i = NUM_BITS-1; i >= 0; --i)
  {
    integer_binary[i] = (int_bits[i] == 1) ? 1 : 0;
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
