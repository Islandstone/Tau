#include <QtGui>
#include "base.h"

#include "timer.h"
//#include "script.h"

#ifdef _WIN32

#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>

#else

#include <time.h>

#endif

/*
void BindTimer()
{
	Sqrat::Class<CTimer, Sqrat::NoConstructor> def;

	//def.Func("Start", &CTimer::Start
	def.Func("CurrentTime", &CTimer::CurrentTime);

	Sqrat::RootTable().Bind("TimerSystem", def);

	// Push the singleton to squirrel
	sq_pushroottable( Sqrat::DefaultVM::Get() );
	sq_pushstring( Sqrat::DefaultVM::Get(), "TimerSystem", -1 );
	sq_get(  Sqrat::DefaultVM::Get(), -2 );
	sq_pushstring(  Sqrat::DefaultVM::Get(), "Timer", -1 );
	sq_createinstance(  Sqrat::DefaultVM::Get(), -2 );
	sq_setinstanceup(  Sqrat::DefaultVM::Get(), -1, (SQUserPointer)Timer() );
	sq_newslot(  Sqrat::DefaultVM::Get(), -4, SQFalse );
	sq_pop(  Sqrat::DefaultVM::Get(), 2 );
}

ClassBinder timerBinder(&BindTimer);
*/

CTimer::CTimer()
{	
#ifdef _WIN32
	m_iStart = 0;
    m_iClockFrequency = -1;
#else 
    m_ulStartTime = 0;
#endif
}

#ifdef _WIN32
__int64 CTimer::GetPerformanceCount()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return li.QuadPart;
}

__int64 CTimer::GetFrequency()
{
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);
    return li.QuadPart;
}
#endif

void CTimer::Start()
{
#ifdef _WIN32
    m_iStart = CTimer::GetPerformanceCount();
    m_iClockFrequency = CTimer::GetFrequency();
#else 
    timespec t;
    clock_gettime(CLOCK_REALTIME, &t);

	m_ulStartTime = (1000000000 * t.tv_sec) + t.tv_nsec;
#endif
	m_bStarted = true;
}

float CTimer::CurrentTime()
{
#ifdef _WIN32
    if (m_iClockFrequency == -1)
    {
        return 0.0f;
    }

    return ((float)(CTimer::GetPerformanceCount() - m_iStart))/(float)m_iClockFrequency;
#else
    timespec t;
    clock_gettime(CLOCK_REALTIME, &t);

	return (((t.tv_sec * 1000000000) + t.tv_nsec) - m_ulStartTime) / 1000000000.0f;
#endif
}

int CTimer::RandomSeed()
{
#ifdef _WIN32
    return GetPerformanceCount() / GetFrequency();
#else
    return 0;
#endif
}

void CTimer::Reset()
{
	m_bStarted = false;

#ifdef _WIN32
    m_iStart = 0;
    m_iClockFrequency = -1;
#endif
}

void CTimer::Restart()
{
    Reset();
	Start();
}
