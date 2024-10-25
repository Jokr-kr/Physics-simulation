#include "CollisionDetect.hpp"
#include "CollisionResolve.hpp"
#include "PhysicsObject.hpp"
#include "Vector2d.hpp"
#include "MathConstants.hpp"

namespace CollisionDetect
{

    bool checkCollision(const PhysicsObject &obj1, const PhysicsObject &obj2)
    {

        float maxDistance = obj1.getHitBox() + obj2.getHitBox() + MathConstants::adjustables::COLLISION_BUFFER;
        ;
        Vector2D delta = obj1.getPosition() - obj2.getPosition();
        float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        return distanceSquared <= maxDistance * maxDistance;
    }

    void detectCircleCollision(PhysicsObject &circle1, PhysicsObject &circle2)
    {
        float distance = circle1.getPosition().distanceTo(circle2.getPosition());

        if (distance < (circle1.getHitBox() + circle2.getHitBox()))
        {
            CollisionResolve::resolveCircleCollision(circle1, circle2);
        }
    };

    void detectSquareCollision(PhysicsObject &square1, PhysicsObject &square2)
    {
        Vector2D *corners1 = square1.getCorners();
        Vector2D *corners2 = square2.getCorners();

        for (int i = 0; i < 4; ++i)
        {
            Vector2D edge1 = corners1[i] - corners1[(i + 1) % 4];
            Vector2D edge2 = corners2[i] - corners2[(i + 1) % 4];

            Vector2D axis1(-edge1.y, edge1.x);
            Vector2D axis2(-edge2.y, edge2.x);

            if (!axisOverlap(corners1, corners2, axis1) || !axisOverlap(corners1, corners2, axis2))
            {
                delete[] corners1;
                delete[] corners2;
                return;
            }
        }
        delete[] corners1;
        delete[] corners2;
        CollisionResolve::resolveSquareCollision(square1, square2);
    };

    void detectCircleSquareCollision(PhysicsObject &circle, PhysicsObject &square)
    {

        Vector2D circlePos = circle.getPosition();
        float radius = circle.getHitBox();
        Vector2D *squareCorners = square.getCorners();

        for (size_t i = 0; i < 4; i++)
        {
            Vector2D start = squareCorners[i];
            Vector2D end = squareCorners[(i + 1) % 4];

            Vector2D edge = end - start;
            Vector2D toCircle = circlePos - start;

            Vector2D edgeNormal(-edge.y, edge.x);
            edgeNormal = edgeNormal.normalize();

            float distance = toCircle.dot(edgeNormal);

            if (abs(distance) <= radius)
            {
                float projection = toCircle.dot(edge) / edge.magnitude();
                if (projection >= 0 && projection <= edge.magnitude())
                {
                    delete[] squareCorners;
                    CollisionResolve::resolveCircleSquareCollision(circle, square);
                    return;
                }
            }
        }
        if (isPointInsideSquare(circlePos, squareCorners))
        {
            delete[] squareCorners;
            CollisionResolve::resolveCircleSquareCollision(circle, square);
            return;
        }
        delete[] squareCorners;
    };

    bool axisOverlap(Vector2D *corners1, Vector2D *corners2, const Vector2D &axis)
    {
        float min1 = corners1[0].dot(axis), max1 = min1;
        float min2 = corners2[0].dot(axis), max2 = min2;

        for (int i = 0; i < 4; ++i)
        {
            float projection1 = corners1[i].dot(axis);
            min1 = minN(min1, projection1);
            max1 = maxN(max1, projection1);

            float projection2 = corners2[i].dot(axis);
            min2 = minN(min2, projection2);
            max2 = maxN(max2, projection2);
        }

        return !(min2 > max1 || min1 > max2);
    }
}

bool isPointInsideSquare(const Vector2D &point, Vector2D *squareCorners)
{
    for (int i = 0; i < 4; ++i)
    {
        Vector2D edge = squareCorners[(i + 1) % 4] - squareCorners[i];
        Vector2D toPoint = point - squareCorners[i];

        if (edge.cross(toPoint) < 0)
        {
            return false;
        }
    }
    return true;
}