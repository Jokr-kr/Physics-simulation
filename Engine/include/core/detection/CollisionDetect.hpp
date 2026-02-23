#ifndef COLLISION_DETECT_HPP
#define COLLISION_DETECT_HPP

#include "PhysicsObject.hpp"
#include "Vector2d.hpp"

namespace CollisionDetect
{
    void detectCircleCollision(PhysicsObject &circle1, PhysicsObject &circle2);
    void detectSquareCollision(PhysicsObject &square1, PhysicsObject &square2);
    void detectCircleSquareCollision(PhysicsObject &circle, PhysicsObject &square);
    // broad-phase check
    bool checkCollision(const PhysicsObject &obj1, const PhysicsObject &obj2);
}

#endif
