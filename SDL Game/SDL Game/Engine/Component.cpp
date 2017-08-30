#include "Component.h"

#include "GameObject.h"


Component::Component()
{
}


Component::~Component()
{
}

std::shared_ptr<GameObject> Component::gameObject()
{
	return m_gameObject.lock();
}
