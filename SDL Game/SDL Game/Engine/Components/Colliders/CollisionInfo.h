#pragma once

#include <memory>
class GameObject;
class Collider;

struct CollisionInfo
{
	std::weak_ptr<GameObject> otherGameObject;
	std::weak_ptr<Collider> otherCollider;
};