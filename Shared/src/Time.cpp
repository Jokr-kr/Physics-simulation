#include "Time.hpp"
#include <thread>
using namespace std::chrono;

time_point<high_resolution_clock> Time::startTime = high_resolution_clock::now();

float Time::getCurrentTimeInMs()
{
    auto currentTime = high_resolution_clock::now();
    auto dur = duration_cast<milliseconds>(currentTime - startTime);
    return static_cast<float>(dur.count());
}

float Time::getCurrentTimeInSeconds()
{
    auto currentTime = high_resolution_clock::now();
    auto dur = duration_cast<duration<float>>(currentTime - startTime);
    return dur.count();
}

void Time::sleepForMs(float ms)
{
    std::this_thread::sleep_for(milliseconds(static_cast<int>(ms)));
}