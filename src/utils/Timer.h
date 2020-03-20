#ifndef __KevEngine_TIMER__
#define __KevEngine_TIMER__

#include <chrono>

using namespace std;
using namespace chrono;

class Timer
{
private:
    unsigned int frames;
    duration<double> timeSpan;
    steady_clock::time_point mainTimerStart;
    steady_clock::time_point mainTimer;

public:
    Timer()
    {
        frames = 0;
        mainTimerStart = steady_clock::now();
    }

    void Start()
    {
        timeSpan = (duration<double>)(0);
        mainTimerStart = steady_clock::now();
        frames = 0;
    }

    void Reset()
    {
        mainTimerStart = steady_clock::now();
    }

    double GetTimePassed() { 
        timeSpan = (steady_clock::now() - mainTimerStart);
        return timeSpan.count();
    }

    unsigned int FrameKeep()
    {
        frames++;
        if (GetTimePassed() >= 1.0f)
        {
            unsigned int thisgoround = frames;
            Reset();
            frames = 0;
            return thisgoround;
        }
        else
        {
            return 0;
        }
    }

    double GetTimePassedReset()
    {
        double time = GetTimePassed();
        Reset();
        return time;
    }

    uint64_t getTimeMS() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); 
    }
};

#endif