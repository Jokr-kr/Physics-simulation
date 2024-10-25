#include "CollisionResolve.hpp"
#include "PhysicsObject.hpp"
#include "Vector2d.hpp"
#include "MathFunctions.hpp"
#include "MathConstants.hpp"

using namespace MathFunctions;
using namespace MathConstants;
using namespace adjustables;

namespace CollisionResolve
{
    void resolveCircleCollision(PhysicsObject &circle1, PhysicsObject &circle2)
    {
        Vector2D collisionNormal = circle2.getPosition() - circle1.getPosition();
        float distance = collisionNormal.magnitude();
        collisionNormal = collisionNormal.normalize();

        float overlap = (circle1.getHitBox() + circle2.getHitBox()) - distance;
        if (overlap > 0)
        {
            Vector2D correction = collisionNormal * (overlap / 2.0f);
            circle1.setPosition(circle1.getPosition() - correction);
            circle2.setPosition(circle2.getPosition() - correction);
        }
        Vector2D r1 = collisionNormal * circle1.getHitBox();
        Vector2D r2 = collisionNormal * circle2.getHitBox();

        Vector2D relativeVelocity =
            (circle2.getVelocity() + r2.perpendicular() * circle2.getAngularVelocity()) -
            (circle1.getVelocity() + r1.perpendicular() * circle1.getAngularVelocity());

        float velocityAlongNormal = relativeVelocity.dot(collisionNormal);
        // if (velocityAlongNormal > 0)return;        //todo add this back in case of performance issues.

        float e = ELASTICITY;
        float impulseScalar = -(1 + e) * velocityAlongNormal /
                              (1 / circle1.getMass() + 1 / circle2.getMass() +
                               (r1.cross(collisionNormal) * r1.cross(collisionNormal)) / circle1.getMomentOfInertia() +
                               (r2.cross(collisionNormal) * r2.cross(collisionNormal)) / circle2.getMomentOfInertia());

        Vector2D impulse = collisionNormal * impulseScalar;
        circle1.setVelocity(circle1.getVelocity() - impulse / circle1.getMass());
        circle2.setVelocity(circle2.getVelocity() + impulse / circle2.getMass());

        circle1.setAngularVelocity(circle1.getAngularVelocity() - (r1.cross(impulse) / circle1.getMomentOfInertia()));
        circle2.setAngularVelocity(circle2.getAngularVelocity() - (r2.cross(impulse) / circle2.getMomentOfInertia()));
    };

    void resolveSquareCollision(PhysicsObject &square1, PhysicsObject &square2)
    {
        Vector2D *corners1 = square1.getCorners();
        Vector2D *corners2 = square2.getCorners();

        Vector2D mtvAxis;
        float minOverlap = LARGE_NUMBER;

        for (int i = 0; i < 4; i++)
        {
            Vector2D edge1 = corners1[i] - corners1[(i + 1) % 4];
            Vector2D axis1 = edge1.perpendicular();
            axis1 = axis1.normalize();

            float overlap1 = calculateOverlap(corners1, corners2, axis1);
            if (overlap1 < minOverlap)
            {
                minOverlap = overlap1;
                mtvAxis = axis1;
            }

            Vector2D edge2 = corners2[i] - corners2[(i + 1) % 4];
            Vector2D axis2 = edge2.perpendicular();

            axis2 = axis2.normalize();

            float overlap2 = calculateOverlap(corners1, corners2, axis1);
            if (overlap2 < minOverlap)
            {
                minOverlap = overlap2;
                mtvAxis = axis2;
            }
        }

        Vector2D correction = mtvAxis * (minOverlap / 2.0f);
        square1.setPosition(square1.getPosition() - correction * (square2.getMass() / (square1.getMass() + square2.getMass())));
        square2.setPosition(square2.getPosition() + correction * (square1.getMass() / (square1.getMass() + square2.getMass())));

        Vector2D collisionPoint = square1.getPosition() + correction;
        Vector2D r1 = collisionPoint - square1.getPosition();
        Vector2D r2 = collisionPoint - square2.getPosition();

        Vector2D relativeVelocity = (square2.getVelocity() + r2.perpendicular() * square2.getAngularVelocity()) -
                                    (square1.getVelocity() + r1.perpendicular() * square1.getAngularVelocity());

        float velocityAlongNormal = relativeVelocity.dot(mtvAxis);

        if (velocityAlongNormal > 0)
        {
            delete[] corners1;
            delete[] corners2;
            return;
        }

        float e = ELASTICITY;
        float r1Cross = r1.cross(mtvAxis);
        float r2Cross = r2.cross(mtvAxis);

        float impulseScalar = -(1 + e) * velocityAlongNormal /
                              ((1 / square1.getMass() + 1 / square2.getMass()) +
                               (r1Cross * r1Cross) / square1.getMomentOfInertia() +
                               (r2Cross * r2Cross) / square2.getMomentOfInertia());

        Vector2D impulse = mtvAxis * impulseScalar;

        square1.setVelocity(square1.getVelocity() - impulse / square1.getMass());
        square1.setVelocity(square2.getVelocity() + impulse / square2.getMass());

        square1.setAngularVelocity(square1.getAngularVelocity() + (r1.cross(impulse) / square1.getMomentOfInertia()));
        square2.setAngularVelocity(square2.getAngularVelocity() + (r2.cross(impulse) / square2.getMomentOfInertia()));

        delete[] corners1;
        delete[] corners2;
    };

    void resolveCircleSquareCollision(PhysicsObject &circle, PhysicsObject &square)
    {
        Vector2D circlePos = circle.getPosition();
        Vector2D *squareCorners = square.getCorners();

        Vector2D closestPoint = squareCorners[0];
        float minDist = circlePos.distanceTo(squareCorners[0]);

        for (int i = 1; i < 4; i++)
        {
            float dist = circlePos.distanceTo(squareCorners[i]);
            if (dist < minDist)
            {
                minDist = dist;
                closestPoint = squareCorners[i];
            }
        }

        for (int i = 0; i < 4; ++i)
        {
            Vector2D start = squareCorners[i];
            Vector2D end = squareCorners[(i + 1) % 4];

            Vector2D edge = end - start;
            Vector2D toCircle = circlePos - start;

            float t = toCircle.dot(edge) / edge.dot(edge);
            t = clamp(t, 0.0f, 1.0f);

            Vector2D projection = start + edge * t;
            float projDist = circlePos.distanceTo(projection);
            if (projDist < minDist)
            {
                minDist = projDist;
                closestPoint = projection;
            }
        }

        Vector2D collisionNormal = (circlePos - closestPoint).normalize();
        float overlap = circle.getHitBox() - minDist;
        if (overlap <= 0)
        {
            delete[] squareCorners;
            return;
        }
        Vector2D correction = collisionNormal * (overlap / 2);
        circle.setPosition(circle.getPosition() + correction * (square.getMass() / (circle.getMass() + square.getMass())));
        square.setPosition(square.getPosition() - correction * (circle.getMass() / (square.getMass() + circle.getMass())));

        Vector2D rCircle = closestPoint - circle.getPosition();
        Vector2D rSquare = closestPoint - square.getPosition();

        Vector2D relativeVelocity = (circle.getVelocity() + rCircle.perpendicular() * circle.getAngularVelocity()) -
                                    (square.getVelocity() + rSquare.perpendicular() * square.getAngularVelocity());

        float velocityAlongNormal = relativeVelocity.dot(collisionNormal);
        if (velocityAlongNormal > 0)
        {
            delete[] squareCorners;
            return;
        }

        float e = ELASTICITY;
        float r1Cross = rCircle.cross(collisionNormal);
        float r2Cross = rSquare.cross(collisionNormal);

        float impulseScalar = -(1 + e) * velocityAlongNormal /
                              ((1 / circle.getMass() + 1 / square.getMass()) +
                               (r1Cross * r1Cross) / circle.getMomentOfInertia() +
                               (r2Cross * r2Cross) / square.getMomentOfInertia());

        Vector2D impulse = collisionNormal * impulseScalar;

        circle.setVelocity(circle.getVelocity() + impulse / circle.getMass());
        square.setVelocity(square.getVelocity() - impulse / square.getMass());

        circle.setAngularVelocity(circle.getAngularVelocity() + (rCircle.cross(impulse) / circle.getMomentOfInertia()));
        square.setAngularVelocity(square.getAngularVelocity() - (rSquare.cross(impulse) / square.getMomentOfInertia()));

        delete[] squareCorners;
    };

    float calculateOverlap(Vector2D *corners1, Vector2D *corners2, const Vector2D &axis)
    {
        float min1 = corners1[0].dot(axis);
        float max1 = min1;

        float min2 = corners2[0].dot(axis);
        float max2 = min2;

        for (int i = 1; i < 4; ++i)
        {
            float projection1 = corners1[i].dot(axis);
            min1 = minN(min1, projection1);
            max1 = maxN(max1, projection1);

            float projection2 = corners2[i].dot(axis);
            min2 = minN(min2, projection2);
            max2 = maxN(max2, projection2);
        }

        // Check for overlap
        float overlap = minN(max1, max2) - maxN(min1, min2);
        return (overlap > 0) ? overlap : 0;
    }
}