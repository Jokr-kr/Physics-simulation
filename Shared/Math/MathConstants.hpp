#ifndef MATHCONSTANTS_HPP
#define MATHCONSTANTS_HPP

namespace MathConstants
{

    // Mathematical Constants
    constexpr float PI = 3.1415926535f;
    constexpr float TWO_PI = 2.0f * PI;
    constexpr float HALF_PI = PI / 2.0f;
    constexpr float E = 2.7182818284f;
    constexpr float SQRT_2 = 1.4142135623f;
    constexpr float SQRT_3 = 1.7320508076f;
    constexpr float GOLDEN_RATIO = 1.6180339887f;
    const float NAN = 0.0f / 0.0f;

    // Angle Conversion Factors
    constexpr float DEG_TO_RAD = PI / 180.0f;
    constexpr float RAD_TO_DEG = 180.0f / PI;

    // other
    constexpr float LARGE_NUMBER = 1e10;

    // adjustable variables
    namespace adjustables
    {
        constexpr float ELASTICITY = 0.8f; // between 0-1
        constexpr float COLLISION_BUFFER = 2.0f;
    }

    // Physical Constants
    namespace Physics
    {
        constexpr float GRAVITY = 9.80665f;                 // Gravitational acceleration (m/s^2)
        constexpr float SPEED_OF_LIGHT = 299792458.0f;      // Speed of light in vacuum (m/s)
        constexpr float PLANCK_CONSTANT = 6.62607015e-34f;  // Planck's constant (J·s)
        constexpr float BOLTZMANN_CONSTANT = 1.380649e-23f; // Boltzmann constant (J/K)
        constexpr float AVOGADRO_CONSTANT = 6.02214076e23f; // Avogadro's number (1/mol)
    }

    // Geometric Constants
    namespace Geometry
    {
        constexpr float CIRCLE_AREA_FACTOR = PI;                   // For area of a circle = PI * r^2
        constexpr float SPHERE_VOLUME_FACTOR = (4.0f / 3.0f) * PI; // For volume of a sphere = (4/3) * PI * r^3
    }

    // Common Fractions
    namespace Fractions
    {
        constexpr float ONE_THIRD = 1.0f / 3.0f;
        constexpr float TWO_THIRDS = 2.0f / 3.0f;
        constexpr float ONE_HALF = 0.5f;
    }

}

#endif