#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

class Time
{
public:
    // Get the current time in milliseconds since the program started
    static float getCurrentTimeInMs();

    // Get the current time in seconds since the program started
    static float getCurrentTimeInSeconds();

    // Delay for a specific number of milliseconds (optional)
    static void sleepForMs(float ms);

private:
    // Starting point for time measurement (used for relative time)
    static std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    // Initialize the starting point (called once at program start)
    static void initializeStartTime();
};

#endif // TIME_HPP