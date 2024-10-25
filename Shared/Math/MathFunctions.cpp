#include "MathFunctions.hpp"
#include "MathConstants.hpp"

using namespace MathConstants;
using namespace MathFunctions;

namespace Mathfunctions
{
    // power and root
    static float sqrt(float x)
    {
        if (x < 0)
        {
            return -1.0f;
        }
        if (x == 0.0f || x == 1.0f)
        {
            return x;
        }

        float guess = x / 2.0f;
        constexpr float epsilon = 1e-6f;

        while (true)
        {
            float nextGuess = (guess + x / guess) / 2.0f;
            if (abs(nextGuess - guess) < epsilon)
            {
                break;
            }
            guess = nextGuess;
        }
        return guess;
    }

    static float invsqrt(float value)
    {
        if (value <= 0.0f)
        {
            return -1.0f;
        }

        long i;
        float x2, y;
        constexpr float threehalfs = 1.5f;

        x2 = value * 0.5f;
        y = value;

        i = *reinterpret_cast<long *>(&y);
        i = 0x5f3759df - (i >> 1); // Magic number and bit manipulation
        y = *reinterpret_cast<float *>(&i);
        y = y * (threehalfs - (x2 * y * y));

        return y;
    }

    static float pow(float base, int exponent)
    {
        // Handle special cases
        if (base == 0.0f && exponent < 0)
        {
            return NAN;
        }

        if (exponent == 0)
        {
            return 1.0f;
        }

        if (exponent < 0)
        {
            return 1.0f / pow(base, -exponent);
        }

        float result = 1.0f;

        for (int i = 0; i < exponent; ++i)
        {
            result *= base;
        }

        return result;
    }

    // trigonimetry
    static float asin(float x)
    {
        if (x < -1.0f || x > 1.0f)
        {
            return NAN;
        }

        float result = 0.0f;
        float term;
        const int numTerms = 10;

        for (int n = 0; n < numTerms; ++n)
        {
            term = (factorial(2 * n) * pow(x, 2 * n + 1)) / (pow(4, n) * pow(factorial(n), 2) * (2 * n + 1));
            result += term;
        }

        return result;
    };

    static float acos(float x)
    {
        if (x < -1.0f || x > 1.0f)
        {
            return NAN;
        }
        return 1.57079633f - asin(x);
    };

    static float atan(float x)
    {
        float result = 0.0f;
        float term;
        const int numTerms = 10;

        for (int n = 0; n < numTerms; ++n)
        {
            term = (n % 2 == 0 ? 1 : -1) * (pow(x, 2 * n + 1) / (2 * n + 1));
            result += term;
        }

        return result;
    };

    static float sin(float degrees)
    {
        // Convert degrees to radians
        float x = degrees * (DEG_TO_RAD);

        while (x < 0)
            x += TWO_PI;
        while (x >= TWO_PI)
            x -= TWO_PI;

        float result = 0.0f;
        float term;
        const int numTerms = 10;

        for (int n = 0; n < numTerms; ++n)
        {
            term = (n % 2 == 0 ? 1 : -1) * (pow(x, 2 * n + 1) / factorial(2 * n + 1));
            result += term;
        }

        return result;
    };

    static float cos(float degrees)
    {
        float x = degrees * (DEG_TO_RAD);

        while (x < 0)
            x += TWO_PI;
        while (x >= TWO_PI)
            x -= TWO_PI;

        float result = 0.0f;
        float term;
        const int numTerms = 10;

        for (int n = 0; n < numTerms; ++n)
        {
            term = (n % 2 == 0 ? 1 : -1) * (pow(x, 2 * n) / factorial(2 * n));
            result += term;
        }

        return result;
    };

    static float tan(float degrees)
    {
        float cosineValue = cos(degrees);
        if (cosineValue == 0.0f)
        {
            return NAN;
        }

        float sineValue = sin(degrees);
        return sineValue / cosineValue;
    };

    // Logarithmic and Exponential Functions
    static float log(float x)
    {
        if (x <= 0.0f)
        {
            return NAN;
        }
        if (x > 1.0f)
        {
            return log(x / E) + 1.0f;
        }

        float result = 0.0f;
        const int numTerms = 10;
        float term = x - 1.0f;

        for (int n = 1; n < numTerms; ++n)
        {
            result += term / n;
            term *= (x - 1.0f);
        }

        return result;
    };

    static float exp(float x)
    {
        float result = 1.0f;
        float term = 1.0f;
        const int numTerms = 10;

        for (int n = 1; n < numTerms; ++n)
        {
            term *= x / n;
            result += term;
        }

        return result;
    };

    // Miscellaneous
    static float clamp(float value, float min, float max)
    {
        if (value < min)
        {
            return min;
        }
        else if (value > max)
        {
            return max;
        }
        return value;
    }

    static float lerp(float a, float b, float t) { return a + (b - a) * t; }
    static float abs(float x) { return (x < 0) ? -x : x; };

    static float sign(float x)
    {
        if (x > 0)
        {
            return 1.0f;
        }
        else if (x < 0)
        {
            return -1.0f;
        }
        return 0.0f;
    }

    static int factorial(int x)
    {
        if (x < 0)
        {
            return NAN;
        }

        int result = 1;
        for (int i = 1; i <= x; ++i)
        {
            result *= i;
        }

        return result;
    }

    float minN(float a, float b) { return (a < b) ? a : b; }
    float maxN(float a, float b) { return (a > b) ? a : b; }
}
