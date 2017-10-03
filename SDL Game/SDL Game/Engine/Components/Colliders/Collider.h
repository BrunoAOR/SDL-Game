#pragma once

#include "Engine/Components/Component.h"

#include <memory>
#include "Engine/Vector2.h"
struct CollisionInfo;


class Collider :
	public Component
{
	friend class CollidersManager;

public:
	Collider();
	virtual ~Collider() = 0;

	Vector2 getLocalPosition();
	Vector2 getWorldPosition();
	double getWorldRotation();

	Vector2 offset;
	bool isStatic;
	bool isTrigger;

	// Callbacks to reroute to Behaviours
	void onCollision(std::shared_ptr<CollisionInfo> info);
	void onTriggerEnter(std::weak_ptr<Collider> other);
	void onTriggerStay(std::weak_ptr<Collider> other);
	void onTriggerExit(std::weak_ptr<Collider> other);
};
