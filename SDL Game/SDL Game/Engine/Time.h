#pragma once

#include <SDL_stdinc.h>


class Time
{
public:
	Time();
	~Time();

	Uint32 time();
	Uint32 deltaTime();

	void updateTime();
	
private:
	Uint32 m_frameStartTime = 0;
	Uint32 m_deltaTime = 0;
};

