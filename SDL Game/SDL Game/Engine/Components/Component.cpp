#include "Component.h"

#include "Engine/Components/ComponentType.h"


// TESTING START
int Component::s_alive = 0;
int Component::s_nextId = 0;
// TESTING END


Component::Component() : m_isActive(true), type(ComponentType::UNDEFINED)
{
	// TESTING START
	m_id = s_nextId++;
	printf("Component constructed -id: %i  ||  Alive: %i\n", m_id, ++s_alive);
	// TESTING END
}


Component::~Component()
{
	// TESTING START
	printf("Component  destructed -id: %i  ||  Alive: %i\n", m_id, --s_alive);
	// TESTING END
}


std::shared_ptr<GameObject> Component::gameObject()
{
	return m_gameObject.lock();
}


void Component::setActive(bool activeState)
{
	m_isActive = activeState;
}


bool Component::isActive()
{
	return m_isActive;
}
