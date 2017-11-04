#include "CollisionCallbackTester.h"

#include "Engine/API/API.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Colliders/Collider.h"
#include "Engine/Components/Colliders/CollisionInfo.h"


void CollisionCallbackTester::start()
{
	m_elapsedTime = 0;
	m_timeLimit = 500;
}

void CollisionCallbackTester::update()
{
	m_elapsedTime += TimeAPI::deltaTime();
}

void CollisionCallbackTester::onCollision(std::shared_ptr<CollisionInfo> info)
{
	if (shouldPrint())
	{
		printf("GO with id %i has collided with GO with id %i\n", gameObject()->m_id, info->otherGameObject.lock()->m_id);
		m_elapsedTime = 0;
	}
}


void CollisionCallbackTester::onTriggerEnter(std::weak_ptr<Collider> other)
{
	printf("GO with id %i has ENTERED a trigger collision with GO with id %i\n", gameObject()->m_id, other.lock()->gameObject()->m_id);
	m_elapsedTime = m_timeLimit;
}


void CollisionCallbackTester::onTriggerStay(std::weak_ptr<Collider> other)
{
	if (shouldPrint())
	{
		printf("GO with id %i is STAYING in a trigger collision with GO with id %i\n", gameObject()->m_id, other.lock()->gameObject()->m_id);
		m_elapsedTime = 0;
	}
}


void CollisionCallbackTester::onTriggerExit(std::weak_ptr<Collider> other)
{
	printf("GO with id %i has EXITED a trigger collision with GO with id %i\n", gameObject()->m_id, other.lock()->gameObject()->m_id);
	m_elapsedTime = m_timeLimit;
}


bool CollisionCallbackTester::shouldPrint()
{
	return (m_elapsedTime >= m_timeLimit);
}
