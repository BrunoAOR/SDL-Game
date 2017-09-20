#include "TimeLogger.h"

#include "Engine/Time.h"

void TimeLogger::start()
{
	m_logInterval = 200;
	m_elapsedInterval = 0;
}

void TimeLogger::update()
{
	int elapsedTime = Time::deltaTime();
	m_elapsedInterval += elapsedTime;
	if (elapsedTime == 0)
	{
		elapsedTime = 1;
	}

	double fps = 1000.0 / elapsedTime;
	m_latestFPS.push_back(fps);
	if (m_latestFPS.size() > 25)
	{
		m_latestFPS.pop_front();
	}

	if (m_elapsedInterval > m_logInterval)
	{
		m_elapsedInterval -= m_logInterval;

		double averageFPS = 0;
		for (double fps : m_latestFPS)
		{
			averageFPS += fps;
		}
		averageFPS /= m_latestFPS.size();
		printf("FPS: %f\n", averageFPS);
	}
}
