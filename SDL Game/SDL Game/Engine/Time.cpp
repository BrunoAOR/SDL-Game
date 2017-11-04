#include "Time.h"
#include <SDL_timer.h>

Time::Time()
{
}


Time::~Time()
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
