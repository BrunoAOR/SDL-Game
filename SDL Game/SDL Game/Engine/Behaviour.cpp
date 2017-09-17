#include "Behaviour.h"


Behaviour::Behaviour()
{
	m_isActive = true;
	m_isAwake = false;
	m_started = false;
}


Behaviour::~Behaviour()
{
}


void Behaviour::setActive(bool activeState)
{
	m_isActive = activeState;
}


bool Behaviour::isActive()
{
	return m_isActive;
}


void Behaviour::awake()
{
}


void Behaviour::start()
{
}

void Behaviour::update()
{
}
