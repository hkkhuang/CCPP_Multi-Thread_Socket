
#ifdef _WIN32

#include <stdio.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "AfFineClock.h"

AfFineClock::AfFineClock()
{
	reset();
}

unsigned int AfFineClock::now()
{
	unsigned int tNow = timeGetTime();
	unsigned int elapsed = tNow - m_startPoint;
	return elapsed;
}

unsigned int AfFineClock::reset()
{
	unsigned int tNow = timeGetTime();
	unsigned int elapsed = tNow - m_startPoint;
	m_startPoint = tNow;
	return elapsed;
}

#endif


