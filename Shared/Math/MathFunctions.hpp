#ifndef MATHFUNCTIONS_HPP
#define MATHFUNCTIONS_HPP

#include "MathConstants.hpp"
using namespace MathConstants;

namespace MathFunctions
{
    // Power and Root Functions
    float sqrt(float x);                 // square root using Newton-Raphson method.
    float invsqrt(float x);              // inverse square, using the fast quake version
    float pow(float base, int exponent); // power function

    // Trigonometric Functions
    float asin(float x); // Arc Sine    Taylor series
    float acos(float x); // Arc Cosine
    float atan(float x); // Arc Tangent
    float sin(float x);  // Sine
    float cos(float x);  // Cosine
    float tan(float x);  // Tangent

    // Logarithmic and Exponential Functions
    float log(float x); // Natural logarithm
    float exp(float x); // Exponential function

    // Miscellaneous
    float clamp(float value, float min, float max); // Clamps value within specified range
    float lerp(float a, float b, float t);          // Linear interpolation
    float abs(float x);                             // Absolute value
    float sign(float x);                            // Sign of a value (-1, 0, or 1)
    int factorial(int n);                           // N!
    float minN(float a, float b);
    float maxN(float a, float b);
};

#endif
