#ifndef API_ENGINE_HPP
#define API_ENGINE_HPP

#include "PhysicsObject.hpp"
#include "MathConstants.hpp"
#include "CollisionDetect.hpp"
#include "CollisionResolve.hpp"
#include "MathFunctions.hpp"

namespace Engine
{
    class APIEngine
    {

    private:
        PhysicsObject *objects;
        int objectCount;
        float timestep;
        float maxFPS;

    public:
        APIEngine(PhysicsObject *objArray, int objCount, float timeStep, float maxFrameRate);

        void run();
        void updateObject();
        void handleCollisions();
        void setMaxFPS(float fps);
    };
}

#endif