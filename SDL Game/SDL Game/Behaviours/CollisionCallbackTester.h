#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"
struct CollisionInfo;


class CollisionCallbackTester :
	public Behaviour
{
public:
	virtual void start() override;
	virtual void update() override;
	virtual void onCollision(std::shared_ptr<CollisionInfo> info) override;
	virtual void onTriggerEnter(std::weak_ptr<Collider> other) override;
	virtual void onTriggerStay(std::weak_ptr<Collider> other) override;
	virtual void onTriggerExit(std::weak_ptr<Collider> other) override;

private:
	int m_elapsedTime;
	int m_timeLimit;

	bool shouldPrint();
};

