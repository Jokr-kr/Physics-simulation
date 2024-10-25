
#ifndef PHYSICSOBJECT_HPP
#define PHYSICSOBJECT_HPP

#include "Vector2D.hpp"
#include "MathFunctions.hpp"

using namespace MathFunctions;

class PhysicsObject
{
public:
    enum ObjectType
    {
        CIRCLE,
        SQUARE,
    };

private:
    ObjectType type;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    float mass;
    float hitBox;   // radius or 2/sidelength
    float friction; // todo: start using this
    float e;        // todo: switch to object based elasticity
    float angle;
    float angularVelocity;
    float angularAcceleration;

public:
    PhysicsObject(ObjectType objType, Vector2D pos, Vector2D vel, float mass, float hitbox)
        : type(objType), position(pos), velocity(vel), acceleration(Vector2D(0, 0)), mass(mass), hitBox(1.0f), friction(0.1f), angle(0.0f), angularVelocity(0.0f), angularAcceleration(0.0f) {}

    void applyForce(const Vector2D &force);
    void update(float deltaTime);

    // checking methods
    bool isCircle() const { return type == CIRCLE; };
    bool isSquare() const { return type == SQUARE; };

    // getters
    ObjectType getType() const { return type; };
    Vector2D getPosition() const { return position; };
    Vector2D getVelocity() const { return velocity; };
    Vector2D getAcceleration() const { return acceleration; };
    float getMass() const { return mass; };
    float getHitBox() const { return hitBox; };
    float getFriction() const { return friction; };
    float getAngle() const { return angle; };
    float getAngularVelocity() { return angularVelocity; };

    // setters
    void setPosition(const Vector2D &pos) { position = pos; };
    void setVelocity(const Vector2D &vel) { velocity = vel; };
    void setAcceleration(const Vector2D &acc) { acceleration = acc; };
    void setMass(float m) { mass = m; };
    void setHitBox(float h) { hitBox = h; };
    void setFriction(float f) { friction = f; };
    void setAngle(float a) { angle = a; };
    void setAngularVelocity(float a) { angularVelocity = a; };

    // calculation methods
    Vector2D *getCorners() const;
    float getMomentOfInertia() const;
};

#endif