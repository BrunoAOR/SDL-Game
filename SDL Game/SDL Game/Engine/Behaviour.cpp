#include "Behaviour.h"


Behaviour::Behaviour()
{
	m_isActive = true;
	m_started = false;
}


void Behaviour::setActive(bool activeState)
{
	m_isActive = activeState;
}

bool Behaviour::isActive()
{
	return m_isActive;
}

Behaviour::~Behaviour()
{

}
