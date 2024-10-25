
#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

class Vector2D
{
public:
    float x, y;

    Vector2D(float x = 0.0f, float y = 0.0f);

    Vector2D operator+(const Vector2D &other) const;
    Vector2D operator-(const Vector2D &other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    float magnitude() const;
    Vector2D normalize() const;

    float dot(const Vector2D &other) const;
    float cross(const Vector2D &other) const;
    float angleBetween(const Vector2D &other) const;
    Vector2D perpendicular() const;
    float distanceTo(const Vector2D &other) const;
    bool isZero() const;
};

#endif