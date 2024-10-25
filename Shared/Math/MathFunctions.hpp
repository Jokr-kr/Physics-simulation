#ifndef MATHFUNCTIONS_HPP
#define MATHFUNCTIONS_HPP

#include "MathConstants.hpp"
using namespace MathConstants;

namespace MathFunctions
{
    // Power and Root Functions
    static float sqrt(float x);                 // square root using Newton-Raphson method.
    static float invsqrt(float x);              // inverse square, using the fast quake version
    static float pow(float base, int exponent); // power function

    // Trigonometric Functions
    static float asin(float x); // Arc Sine    Taylor series
    static float acos(float x); // Arc Cosine
    static float atan(float x); // Arc Tangent
    static float sin(float x);  // Sine
    static float cos(float x);  // Cosine
    static float tan(float x);  // Tangent

    // Logarithmic and Exponential Functions
    static float log(float x); // Natural logarithm
    static float exp(float x); // Exponential function

    // Miscellaneous
    static float clamp(float value, float min, float max); // Clamps value within specified range
    static float lerp(float a, float b, float t);          // Linear interpolation
    static float abs(float x);                             // Absolute value
    static float sign(float x);                            // Sign of a value (-1, 0, or 1)
    static int factorial(int n);                           // N!
    static float minN(float a, float b);
    static float maxN(float a, float b);
};

#endif