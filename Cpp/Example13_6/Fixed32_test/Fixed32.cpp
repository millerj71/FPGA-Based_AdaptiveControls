
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
}

void Fixed32::updateBitsRepresentation(const double& rhs)
{
  double RHS = (rhs < 0) ? -rhs : rhs;
  double exp, decr;
  std::bitset<32> mag;
  for (int i = 0; i < NUM_BITS; i++)
  {
    exp  = pow(2, NUM_WHOLE_BITS+1 - i);
    decr = (RHS > exp) ? exp : 0;
    RHS  = RHS - decr;

    mag[NUM_BITS-1 - i]  = (decr != 0) ? 1 : 0;

  }

  int32_t value = static_cast<int32_t>(mag.to_ulong());

  bits = (rhs < 0) ? std::bitset<32>(-value) : std::bitset<32>(value);
  
}

void Fixed32::updateBitsRepresentation(const int32_t& rhs)
{
  bits = std::bitset<32>(rhs);
}

void Fixed32::updateBitsRepresentation(const std::string& rhs)
{
  if (rhs.length() != NUM_BITS) { return; }
  bits = std::bitset<32>(rhs);
}




// Update Other Representations
void Fixed32::updateRemainingRepresentations()
{
  updateIntegerRepresentation();
  updateStringRepresentation();
  updateDoubleRepresentation();
}

void Fixed32::updateStringRepresentation()
{
  str_value = bits.to_string();
}

void Fixed32::updateDoubleRepresentation()
{
  double update = 0;
  double incr;
  std::bitset<32> mag(abs(integer));

  for (int i = 0; i < NUM_BITS; i++)
  {
    incr    = (mag[i]) ? pow(2, i+1 - NUM_DECIMAL_BITS) : 0;
    update  = update + incr;
  }

  double_value = (integer < 0) ? -update : update;

}

void Fixed32::updateIntegerRepresentation()
{
  integer = static_cast<int32_t>(bits.to_ulong());
}




// Print Functions for Testing
void Fixed32::print()
{
  printBits();
  printString();
  printDouble();
  printInteger();
}

void Fixed32::printBits()
{
  std::cout << "bits   = " <<  bits << std::endl;
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
