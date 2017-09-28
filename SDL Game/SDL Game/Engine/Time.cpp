#include "Time.h"


Uint32 Time::m_frameStartTime = 0;
Uint32 Time::m_deltaTime = 0;


Time::Time()
{
}


Uint32 Time::time()
{
	return m_frameStartTime;
}


Uint32 Time::deltaTime()
{
	return m_deltaTime;
}


void Time::updateTime()
{
	unsigned int currentTicks = SDL_GetTicks();
	m_deltaTime = currentTicks - m_frameStartTime;
	m_frameStartTime = currentTicks;
}
