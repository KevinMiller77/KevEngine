#ifndef __TLETC_TIMER__
#define __TLETC_TIMER__

#include <chrono>

using namespace std;
using namespace chrono;

class Timer
{
private:
    unsigned int frames;
    duration<double> timeSpan{};
    steady_clock::time_point mainTimer;

public:
    Timer()
    {
        frames = 0;
        mainTimer = steady_clock::now();
    }

    void reset()
    {
        mainTimer = steady_clock::now();
    }

    double getTimePassed()
    {
        timeSpan = duration_cast<duration<double>>(steady_clock::now() - mainTimer);
        return timeSpan.count();
    }

    double getTimePassedReset()
    {
        double time = getTimePassed();
        reset();
        return time;
    }
};

#endif