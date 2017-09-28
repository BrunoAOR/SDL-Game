#pragma once

#include <SDL.h>


class Time
{
public:
	static Uint32 time();
	static Uint32 deltaTime();

	static void updateTime();
	
private:
	Time();

	static Uint32 m_frameStartTime;
	static Uint32 m_deltaTime;
};

