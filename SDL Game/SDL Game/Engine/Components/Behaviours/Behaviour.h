#pragma once

#include "Engine/Components/Component.h"
#include <memory>
class Collider;
struct CollisionInfo;


class Behaviour :
	public Component
{
	friend class BehavioursManager;

public:	
	Behaviour();
	virtual ~Behaviour() = 0;

	// Defining methods for behaviours to implement
	// Lifecycle related
	virtual void awake();
	virtual void start();
	virtual void update();
	// Collisions related
	virtual void onCollision(std::shared_ptr<CollisionInfo> info);
	virtual void onTriggerEnter(std::weak_ptr<Collider> other);
	virtual void onTriggerStay(std::weak_ptr<Collider> other);
	virtual void onTriggerExit(std::weak_ptr<Collider> other);

private:
	bool m_isAwake;
	bool m_started;
};
