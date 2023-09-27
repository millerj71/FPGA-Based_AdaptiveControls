#include <cmath>
#include <cstdio>
#include <string>
#include <bitset>

#include "Fixed32.h"


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

Fixed32 operator+(const Fixed32& a, const int32_t& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a + B;
}

Fixed32 operator+(const int32_t& a, const Fixed32& b)
{
  Fixed32 output(b.NUM_DECIMAL_BITS);
  output = b + a;
  return output;
}

Fixed32 operator+(const Fixed32& a, const std::string& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a + B;
}

Fixed32 operator+(const std::string& a, const Fixed32& b)
{
  Fixed32 output(b.NUM_DECIMAL_BITS);
  output = b + a;
  return output;
}




// Overloading "-" Operator (Uniary Subtraction)
Fixed32 Fixed32::operator-()
{
  Fixed32 output(NUM_DECIMAL_BITS);
  output = -integer;
  return output;
}

// Overloading "-" Operator (Subtraction)
Fixed32 operator-(const Fixed32& a, const Fixed32& b)
{
  Fixed32 A(a.NUM_DECIMAL_BITS);
  Fixed32 B(b.NUM_DECIMAL_BITS);
  Fixed32 output(a.NUM_DECIMAL_BITS);

  A = a;
  B = b;
  output = A + (-B);

  return output;
}

Fixed32 operator-(const Fixed32& a, const double& b)
{
  Fixed32 A(a.NUM_DECIMAL_BITS);
  Fixed32 B(a.NUM_DECIMAL_BITS);
  A = a;
  B = b;
  return A - B;  
}

Fixed32 operator-(const double& a, const Fixed32& b)
{
  Fixed32 A(b.NUM_DECIMAL_BITS);
  Fixed32 B(b.NUM_DECIMAL_BITS);
  A = a;
  B = b;
  return A - B; 
}

Fixed32 operator-(const Fixed32& a, const int32_t& b)
{
  Fixed32 A(a.NUM_DECIMAL_BITS);
  Fixed32 B(a.NUM_DECIMAL_BITS);
  A = a;
  B = b;
  return A - B;
}

Fixed32 operator-(const int32_t& a, const Fixed32& b)
{
  Fixed32 A(b.NUM_DECIMAL_BITS);
  Fixed32 B(b.NUM_DECIMAL_BITS);
  A = a;
  B = b;
  return A - B; 
}

Fixed32 operator-(const Fixed32& a, const std::string& b)
{
  Fixed32 A(a.NUM_DECIMAL_BITS);
  Fixed32 B(a.NUM_DECIMAL_BITS);
  A = a;
  B = b;
  return A - B;
}

Fixed32 operator-(const std::string& a, const Fixed32& b)
{
  Fixed32 A(b.NUM_DECIMAL_BITS);
  Fixed32 B(b.NUM_DECIMAL_BITS);
  A = a;
  B = b;
  return A - B; 
}




// Overloading * Operator
Fixed32 operator*(const Fixed32& a, const Fixed32& b)
{
  Fixed32 output(a.NUM_DECIMAL_BITS);

  // a.integer and b.integer are int32_t and need to be converted to int64_t
  // before the multiplication step to avoid some binary weirdness.
  int64_t A = a.integer;
  int64_t B = b.integer;
  int64_t C = A * B;

  // Removing the decimal points that are out of the Fixed32 output's range.
  C = C >> (a.NUM_DECIMAL_BITS - 1);

  std::bitset<64> bits(C);

  std::string output_string;
  output_string.resize(output.NUM_BITS);

  for (int i = 0; i < output.NUM_BITS; i++)
  {
    output_string[output.NUM_BITS-1 - i] = '0';
    if (bits[i] == 1)
    {
      output_string[output.NUM_BITS-1 - i] = '1';
    }
  }

  output = output_string;
  return output;
}

Fixed32 operator*(const Fixed32& a, const double& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a * B;
}

Fixed32 operator*(const double& a, const Fixed32& b)
{
  Fixed32 output(b.NUM_DECIMAL_BITS);
  output = b * a;
  return output;
}

Fixed32 operator*(const Fixed32& a, const int32_t& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a * B;
}

Fixed32 operator*(const int32_t& a, const Fixed32& b)
{
  Fixed32 output(b.NUM_DECIMAL_BITS);
  output = b * a;
  return output;
}

Fixed32 operator*(const Fixed32& a, const std::string& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a * B;
}

Fixed32 operator*(const std::string& a, const Fixed32& b)
{
  Fixed32 output(b.NUM_DECIMAL_BITS);
  output = b * a;
  return output;
}




// Overloading "/" Operator
Fixed32 operator/(const Fixed32& a, const Fixed32& b)
{
  // This "/" function can result in the integer representation of the
  // answer being slightly off. It doesn't yet appear to affect the double
  // result and should be close enough to work for our purposes.
  int64_t A = static_cast<int64_t>(a.integer) << 32;
  int64_t B = b.integer;
  int64_t OUT = (A / B) >> 32 - a.NUM_DECIMAL_BITS+1;

  Fixed32 output(a.NUM_DECIMAL_BITS);
  output = static_cast<int32_t>(OUT);
  return output;
}

Fixed32 operator/(const Fixed32& a, const double& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a / B;
}

Fixed32 operator/(const double& a, const Fixed32& b)
{
  Fixed32 A(b.NUM_DECIMAL_BITS);
  Fixed32 output(b.NUM_DECIMAL_BITS);
  A = a;
  output = A / b;
  return output;
}

Fixed32 operator/(const Fixed32& a, const int32_t& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a / B;
}

Fixed32 operator/(const int32_t& a, const Fixed32& b)
{
  Fixed32 A(b.NUM_DECIMAL_BITS);
  Fixed32 output(b.NUM_DECIMAL_BITS);
  A = a;
  output = A / b;
  return output;
}

Fixed32 operator/(const Fixed32& a, const std::string& b)
{
  Fixed32 B(a.NUM_DECIMAL_BITS);
  B = b;
  return a / B;
}

Fixed32 operator/(const std::string& a, const Fixed32& b)
{
  Fixed32 A(b.NUM_DECIMAL_BITS);
  Fixed32 output(b.NUM_DECIMAL_BITS);
  
  A = a;
  output = A / b;
  return output;
}