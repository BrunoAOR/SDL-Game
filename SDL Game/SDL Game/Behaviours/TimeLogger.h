#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"

#include <deque>


class TimeLogger :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

private:
	std::deque<double> m_latestFPS;
	int m_logInterval;
	int m_elapsedInterval;
};

