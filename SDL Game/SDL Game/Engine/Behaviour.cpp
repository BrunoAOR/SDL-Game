#include "Behaviour.h"

#include "BehavioursManager.h"


Behaviour::Behaviour()
{
	m_gameObject = nullptr;
	m_started = false;
	BehavioursManager::subscribeBehaviour(this);
}


Behaviour::~Behaviour()
{
	BehavioursManager::unsubscribeBehaviour(this);
}


GameObject * Behaviour::gameObject()
{
	return m_gameObject;
}
