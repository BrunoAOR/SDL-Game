#include "Collider.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Components/Behaviours/Behaviour.h"
#include "Engine/Components/ComponentType.h"
#include "Engine/Components/Colliders/CollisionInfo.h"


Collider::Collider() : offset(0, 0), isStatic(false), isTrigger(false)
{
	type = ComponentType::Collider;
}


Collider::~Collider()
{
}


Vector2 Collider::getLocalPosition()
{
	auto transform = gameObject()->transform.lock();
	Vector2 localPos = transform->getLocalPosition() + offset;
	return localPos;
}


Vector2 Collider::getWorldPosition()
{
	auto transform = gameObject()->transform.lock();
	Vector2 worldPos = transform->getLocalPosition() + offset;
	worldPos = transform->localToWorldPosition(worldPos);
	return worldPos;
}


double Collider::getWorldRotation()
{
	return gameObject()->transform.lock()->getWorldRotation();
}


void Collider::onCollision(std::shared_ptr<CollisionInfo> info)
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto weakBehaviour : behaviours)
	{
		if (auto behaviour = weakBehaviour.lock())
		{
			behaviour->onCollision(info);
		}
	}
}


void Collider::onTriggerEnter(std::weak_ptr<Collider> other)
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto weakBehaviour : behaviours)
	{
		if (auto behaviour = weakBehaviour.lock())
		{
			behaviour->onTriggerEnter(other);
		}
	}
}


void Collider::onTriggerStay(std::weak_ptr<Collider> other)
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto weakBehaviour : behaviours)
	{
		if (auto behaviour = weakBehaviour.lock())
		{
			behaviour->onTriggerStay(other);
		}
	}
}


void Collider::onTriggerExit(std::weak_ptr<Collider> other)
{
	auto behaviours = gameObject()->getComponents<Behaviour>();
	for (auto weakBehaviour : behaviours)
	{
		if (auto behaviour = weakBehaviour.lock())
		{
			behaviour->onTriggerExit(other);
		}
	}
}
