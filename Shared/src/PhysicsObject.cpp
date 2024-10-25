#include "PhysicsObject.hpp"
#include "MathFunctions.hpp"
#include "MathConstants.hpp"
#include "Vector2D.hpp"

using namespace MathFunctions;

PhysicsObject::PhysicsObject(ObjectType objType, Vector2D pos, Vector2D vel, float m, float h)
    : type(objType), position(pos), velocity(vel), acceleration(Vector2D(0, 0)), mass(m),
      hitBox(h), friction(0.1f), angle(0.0f), angularVelocity(0.0f), angularAcceleration(0.0f) {}

void PhysicsObject::applyForce(const Vector2D &force)
{
    acceleration = acceleration + (force / mass); // todo: take another look at this
}

void PhysicsObject::update(float deltaTime)
{
    velocity = velocity + acceleration * deltaTime;

    velocity = velocity * (1.0f - friction);

    position = position + velocity * deltaTime;

    acceleration = Vector2D(0, 0);
}

// calculation methods
Vector2D *PhysicsObject::getCorners() const
{
    Vector2D *corners = new Vector2D[4];
    float halfWidth = hitBox / 2.0f; //

    Vector2D topLeft(-halfWidth, halfWidth);
    Vector2D topRight(halfWidth, halfWidth);
    Vector2D bottomRight(-halfWidth, -halfWidth);
    Vector2D bottomLeft(halfWidth, -halfWidth);

    corners[0] = Vector2D(
        position.x + topLeft.x * cos(angle) - topLeft.y * sin(angle),
        position.y + topLeft.x * sin(angle) + topLeft.y * cos(angle));

    corners[1] = Vector2D(
        position.x + topRight.x * cos(angle) - topRight.y * sin(angle),
        position.y + topRight.x * sin(angle) + topRight.y * cos(angle));

    corners[2] = Vector2D(
        position.x + bottomRight.x * cos(angle) - bottomRight.y * sin(angle),
        position.y + bottomRight.x * sin(angle) + bottomRight.y * cos(angle));

    corners[3] = Vector2D(
        position.x + bottomLeft.x * cos(angle) - bottomLeft.y * sin(angle),
        position.y + bottomLeft.x * sin(angle) + bottomLeft.y * cos(angle));

    return corners;
}

float PhysicsObject::getMomentOfInertia() const
{
    if (isCircle())
    {
        return 0.5f * mass * hitBox * hitBox;
    }
    else if (isSquare())
    {
        return (1.0f / 6.0f) * mass * hitBox * hitBox;
    }
    return 0.0f;
}
