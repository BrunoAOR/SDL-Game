#include "Collider.h"

#include "GameObject.h"


Collider::Collider() : offset(0, 0), isStatic(false), isTrigger(false)
{
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
