#include "Vector2d.hpp"
#include "MathConstants.hpp"
#include "MathFunctions.hpp"
using namespace MathFunctions;
using namespace MathConstants;

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D &other) const { return Vector2D(x + other.x, y + other.y); }
Vector2D Vector2D::operator-(const Vector2D &other) const { return Vector2D(x - other.x, y - other.y); }
Vector2D Vector2D::operator*(float scalar) const { return Vector2D(x * scalar, y * scalar); }
Vector2D Vector2D::operator/(float scalar) const

{
    if (scalar == 0.0f)
    {
        return Vector2D(0, 0);
    }
    else
        return Vector2D(x / scalar, y / scalar);
}

float Vector2D::magnitude() const { return sqrt(x * x + y * y); }

Vector2D Vector2D::normalize() const
{
    float mag = magnitude();
    return (mag > 0) ? *this / mag : Vector2D(0, 0);
}

float Vector2D::dot(const Vector2D &other) const { return x * other.x + y * other.y; }

float Vector2D::cross(const Vector2D &other) const { return x * other.y - y * other.x; }

float Vector2D::angleBetween(const Vector2D &other) const
{
    float dotProd = dot(other);
    float mags = magnitude() * other.magnitude();
    return (mags > 0) ? acos(dotProd / mags) : 0.0f; // remember! Result in radians
}

Vector2D Vector2D::perpendicular() const { return Vector2D(-y, x); }

float Vector2D::distanceTo(const Vector2D &other) const { return (*this - other).magnitude(); }

bool Vector2D::isZero() const { return x == 0.0f && y == 0.0f; }
