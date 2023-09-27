

#ifndef FIXED32_H
#define FIXED32_H

#include <iostream>
#include <string>
#include <vector>

class Fixed32
{

  public: 
    const int NUM_BITS   = 32;
    const int NUM_VALUE_BITS = 31;
    int NUM_DECIMAL_BITS = 16;
    int NUM_WHOLE_BITS   = 15;

    bool binary[32];
    bool binary_mag[32];
    bool integer_binary[32];
    double  double_value;
    int32_t integer;
    std::string str_value;

    bool isNegative;

    // Constructors
    Fixed32();
    Fixed32(int num_dec);
    
    // Destructors
    ~Fixed32();

    // Misc Functions
    void applyTwosCompliment();

    // Print Values
    void print();
    void printBinary();
    void printString();
    void printDouble();
    void printInteger();
    void printIntegerBinary();

    // Update Values
    void updateValueRepresentations(const Fixed32& rhs);
    void updateValueRepresentations(const double& rhs);
    void updateValueRepresentations(const int32_t& rhs);
    void updateValueRepresentations(const std::string& rhs);

    // Update Binary Values
    void updateBinaryRepresentation(const Fixed32& rhs);
    void updateBinaryRepresentation(const double& rhs);
    void updateBinaryRepresentation(const int32_t& rhs);
    void updateBinaryRepresentation(const std::string& rhs);

    // Update Other Values
    void updateRemainingRepresentations();
    void updateStringRepresentation();
    void updateDoubleRepresentation();
    void updateIntegerRepresentation();
    void updateIntegerBinaryRepresentation();

    // Overloading "=" Operator
    Fixed32& operator=(const Fixed32& rhs);
    Fixed32& operator=(const double& rhs);
    Fixed32& operator=(const int32_t& rhs);
    Fixed32& operator=(const std::string& rhs);

    // Overloading "-" Operator (unary)
    Fixed32 operator-();

};


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