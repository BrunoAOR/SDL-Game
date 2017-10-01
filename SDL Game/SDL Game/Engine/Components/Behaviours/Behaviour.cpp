#include "Behaviour.h"

#include "Engine/Components/ComponentType.h"


Behaviour::Behaviour()
{
	type = ComponentType::Behaviour;
	m_isAwake = false;
	m_started = false;
}


Behaviour::~Behaviour()
{
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
