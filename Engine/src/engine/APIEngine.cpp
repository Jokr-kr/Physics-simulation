#include "APIEngine.hpp"
#include <chrono>
#include <thread>
using namespace std;

namespace Engine
{

    APIEngine::APIEngine(PhysicsObject *objArray, int objCount, float timeStep, float maxFrameRate)
        : objects(objArray), objectCount(objCount), timestep(timeStep), maxFPS(maxFrameRate) {}

    void APIEngine::run()
    {
        while (true)
        {
            auto start = chrono::high_resolution_clock::now();
            updateObject();
            handleCollisions();
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<float> elapsed = end - start;
            float frameTime = 1.0f - maxFPS;
            if (elapsed.count() < frameTime)
            {
                this_thread::sleep_for(chrono::duration<float>(frameTime - elapsed.count()));
            }
        }
    }

    void APIEngine::updateObject()
    {
        for (int i = 0; i < objectCount; i++)
        {
            objects[i].applyForce(timestep);
            objects[i].updatePosition(timestep);
        }
    }

    void APIEngine::handleCollisions()
    {
        for (int i = 0; i < objectCount; i++)
        {
            for (int j = 0; j < objectCount; j++)
            {
                PhysicsObject &obj1 = objects[i];
                PhysicsObject &obj2 = objects[j];
                if (CollisionDetect::checkCollision(obj1, obj2))
                {
                    int typeCode = obj1.getType() * 10 + obj2.getType();
                    switch (typeCode)
                    {
                    case 11:
                        CollisionDetect::detectCircleCollision(obj1, obj2);
                        break;
                    case 12:
                        CollisionDetect::detectCircleSquareCollision(obj1, obj2);
                        break;
                    case 21:
                        CollisionDetect::detectCircleSquareCollision(obj2, obj1);
                        break;
                    case 22:
                        CollisionDetect::detectCircleSquareCollision(obj1, obj2);
                        break;
                    }
                }
            }
        }
    }
    void APIEngine::setMaxFPS(float fps)
    {
        maxFPS = fps;
    }

}