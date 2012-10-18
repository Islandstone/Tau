#ifndef TIMER_H
#define TIMER_H

#include "itimer.h"

class CTimer : public ITimer
{
public:
    CTimer();

    // This is only a singleton for the global timer.
    // User code may create CTimer objects as they wish if neccessary
    static CTimer* GlobalTimer()
    {
        static CTimer globalTimer;
        return &globalTimer;
    }

    float CurrentTime();

    virtual void Start();
    virtual void Reset();
    virtual void Restart();

    bool IsStarted() { return m_bStarted; }

	int RandomSeed();

protected:

    bool m_bStarted;

private:

#ifdef _WIN32
	__int64 GetPerformanceCount();
	__int64 GetFrequency();

	__int64 m_iStart;
	__int64 m_iClockFrequency;
#endif 

	unsigned long m_ulStartTime;
};

extern inline ITimer* Timer()
{
    return CTimer::GlobalTimer();
}

#endif // TIMER_H
