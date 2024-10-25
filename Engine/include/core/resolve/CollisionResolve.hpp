#ifndef COLLISION_RESOLVE_HPP
#define COLLISION_RESOLVE_HPP

#include "PhysicsObject.hpp"
#include "Vector2d.hpp"

namespace CollisionResolve
{
    void resolveCircleCollision(PhysicsObject &obj1, PhysicsObject &obj2);
    void resolveSquareCollision(PhysicsObject &obj1, PhysicsObject &obj2);
    void resolveCircleSquareCollision(PhysicsObject &circle, PhysicsObject &square);
}
#endif