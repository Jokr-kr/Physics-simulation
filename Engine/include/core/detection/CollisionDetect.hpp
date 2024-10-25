#ifndef COLLISION_DETECT_HPP
#define COLLISION_DETECT_HPP

#include "PhysicsObject.hpp"
#include "Vector2d.hpp"

namespace CollisionDetect
{
    bool detectCircleCollision(const PhysicsObject &circle1, const PhysicsObject &circle2);
    bool detectSquareCollision(const PhysicsObject &square1, const PhysicsObject &square2);
    bool detectCircleSquareCollision(const PhysicsObject &circle, const PhysicsObject &square);
    // broad-phase check
    bool checkCollision(const PhysicsObject &obj1, const PhysicsObject &obj2);
}

#endif