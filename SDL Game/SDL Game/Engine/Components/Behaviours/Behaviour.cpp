#include "Behaviour.h"

#include "Engine/Components/ComponentType.h"
#include "Engine/Components/Colliders/Collider.h"
#include "Engine/Components/Colliders/CollisionInfo.h"


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


void Behaviour::onCollision(std::shared_ptr<CollisionInfo> info)
{
}


void Behaviour::onTriggerEnter(std::weak_ptr<Collider> other)
{
}


void Behaviour::onTriggerStay(std::weak_ptr<Collider> other)
{
}


void Behaviour::onTriggerExit(std::weak_ptr<Collider> other)
{
}
