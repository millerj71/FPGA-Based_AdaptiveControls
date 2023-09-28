

#ifndef FIXED32_H
#define FIXED32_H

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

class Fixed32
{

  public: 
    const int NUM_BITS   = 32;
    const int NUM_VALUE_BITS = 31;
    int NUM_DECIMAL_BITS = 16;
    int NUM_WHOLE_BITS   = 15;

    std::bitset<32> bits;
    double  double_value;
    int32_t integer;
    std::string str_value;

    // Constructors
    Fixed32();
    Fixed32(int num_dec);
    
    // Destructors
    ~Fixed32();

    // Misc Functions
    Fixed32 inv();

    // Print Values
    void print();
    void printBits();
    void printString();
    void printDouble();
    void printInteger();

    // Update Values
    void updateValueRepresentations(const Fixed32& rhs);
    void updateValueRepresentations(const double& rhs);
    void updateValueRepresentations(const int32_t& rhs);
    void updateValueRepresentations(const std::string& rhs);

    // Update Bit Values
    void updateBitsRepresentation(const Fixed32& rhs);
    void updateBitsRepresentation(const double& rhs);
    void updateBitsRepresentation(const int32_t& rhs);
    void updateBitsRepresentation(const std::string& rhs);

    // Update Other Values
    void updateRemainingRepresentations();
    void updateStringRepresentation();
    void updateDoubleRepresentation();
    void updateIntegerRepresentation();

    // Overloading "=" Operator
    Fixed32& operator=(const Fixed32& rhs);
    Fixed32& operator=(const double& rhs);
    Fixed32& operator=(const int32_t& rhs);
    Fixed32& operator=(const std::string& rhs);

    // Overloading "-" Operator (unary)
    Fixed32 operator-();

};



// Misc Functions
Fixed32 inv(const Fixed32& input);


// Overloading "+" Operator
Fixed32 operator+(const Fixed32& a, const Fixed32& b);
Fixed32 operator+(const Fixed32& a, const double& b);
Fixed32 operator+(const double& a, const Fixed32& b);
Fixed32 operator+(const Fixed32& a, const int32_t& b);
Fixed32 operator+(const int32_t& a, const Fixed32& b);
Fixed32 operator+(const Fixed32& a, const std::string& b);
Fixed32 operator+(const std::string& a, const Fixed32& b);

// Overloading "-" Operator
Fixed32 operator-(const Fixed32& a, const Fixed32& b);
Fixed32 operator-(const Fixed32& a, const double& b);
Fixed32 operator-(const double& a, const Fixed32& b);
Fixed32 operator-(const Fixed32& a, const int32_t& b);
Fixed32 operator-(const int32_t& a, const Fixed32& b);
Fixed32 operator-(const Fixed32& a, const std::string& b);
Fixed32 operator-(const std::string& a, const Fixed32& b);

// Overloading "*" Operator
Fixed32 operator*(const Fixed32& a, const Fixed32& b);
Fixed32 operator*(const Fixed32& a, const double& b);
Fixed32 operator*(const double& a, const Fixed32& b);
Fixed32 operator*(const Fixed32& a, const int32_t& b);
Fixed32 operator*(const int32_t& a, const Fixed32& b);
Fixed32 operator*(const Fixed32& a, const std::string& b);
Fixed32 operator*(const std::string& a, const Fixed32& b);

// Overloading "/" Operator
Fixed32 operator/(const Fixed32& a, const Fixed32& b);
Fixed32 operator/(const Fixed32& a, const double& b);
Fixed32 operator/(const double& a, const Fixed32& b);
Fixed32 operator/(const Fixed32& a, const int32_t& b);
Fixed32 operator/(const int32_t& a, const Fixed32& b);
Fixed32 operator/(const Fixed32& a, const std::string& b);
Fixed32 operator/(const std::string& a, const Fixed32& b);


#endif // FIXED32_H