#include "Collider.h"

#include "GameObject.h"


Collider::Collider() : offset(0, 0), isStatic(false), isTrigger(false)
{
}


Collider::~Collider()
{
}

Vector2 Collider::getWorldPosition()
{
	Transform& transform = gameObject()->transform;
	Vector2 transformPos = transform.getLocalPosition();
	Vector2 worldPos = transform.getLocalPosition() + offset;
	worldPos = transform.localToWorldPosition(worldPos);
	return worldPos;
}
