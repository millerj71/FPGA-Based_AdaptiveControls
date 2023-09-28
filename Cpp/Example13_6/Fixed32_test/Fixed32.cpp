
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
  updateBitsRepresentation(rhs);
  updateRemainingRepresentations();
}

void Fixed32::updateValueRepresentations(const double& rhs)
{
  updateBitsRepresentation(rhs);
  updateRemainingRepresentations();
}

void Fixed32::updateValueRepresentations(const int32_t& rhs)
{
  updateBitsRepresentation(rhs);
  updateRemainingRepresentations();
}

void Fixed32::updateValueRepresentations(const std::string& rhs)
{
  updateBitsRepresentation(rhs);
  updateRemainingRepresentations();
}




// Update Bit Values
void Fixed32::updateBitsRepresentation(const Fixed32& rhs)
{
  bits = rhs.bits;
  mag_bits = rhs.mag_bits;
  isNegative = rhs.isNegative;
}

void Fixed32::updateBitsRepresentation(const double& rhs)
{
  isNegative = (rhs < 0) ? 1 : 0;
  double RHS = (rhs < 0) ? -rhs : rhs;
  double exp, decr;
  for (int i = 0; i < NUM_BITS; i++)
  {
    exp  = pow(2, NUM_WHOLE_BITS+1 - i);
    decr = (RHS > exp) ? exp : 0;
    RHS  = RHS - decr;

    mag_bits[NUM_BITS-1 - i]  = (decr != 0) ? 1 : 0;
  }


  int32_t value = static_cast<int32_t>(mag_bits.to_ulong());
  
  bits = (isNegative) ? std::bitset<32>(-value) : std::bitset<32>(value);
  
}

void Fixed32::updateBitsRepresentation(const int32_t& rhs)
{
  bits = std::bitset<32>(rhs);
  mag_bits = std::bitset<32>(abs(rhs));
  isNegative = (bits != mag_bits) ? 1 : 0;
}

void Fixed32::updateBitsRepresentation(const std::string& rhs)
{
  if (rhs.length() != NUM_BITS) { return; }

  bits = std::bitset<32>(rhs);
  isNegative = (bits[NUM_BITS-1] == 1) ? 1 : 0;

  int32_t value = static_cast<int32_t>(bits.to_ulong());
  mag_bits = (isNegative) ? std::bitset<32>(-value) : bits;
}




// Update Other Representations
void Fixed32::updateRemainingRepresentations()
{
  updateBinaryRepresentation();
  updateStringRepresentation();
  updateDoubleRepresentation();
  updateIntegerRepresentation();
  updateIntegerBinaryRepresentation();  
}

void Fixed32::updateBinaryRepresentation()
{
  for (int i = 0; i < NUM_BITS; i++)
  {
    binary[i] = bits[i];
    binary_mag[i] = mag_bits[i];
  }
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
    incr    = (mag_bits[i]) ? pow(2, i+1 - NUM_DECIMAL_BITS) : 0;
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


// Misc Functions
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
  printBits();
  printBinary();
  printString();
  printDouble();
  printInteger();
  printIntegerBinary();
}

void Fixed32::printBits()
{
  std::cout << "bits   = " <<  bits << std::endl;
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
