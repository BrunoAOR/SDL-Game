#include "CollidersManager.h"

#include <cmath>
#include "EngineUtils.h"
#include "Vector2.h"
#include "GameObject.h"


const double CollidersManager::MinPenetration = 0.01;

CollidersManager::CollidersManager()
{
}


CollidersManager::~CollidersManager()
{
}


bool CollidersManager::canManage(std::weak_ptr<Component> component)
{
	if (std::dynamic_pointer_cast<Collider>(component.lock()))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CollidersManager::update()
{
	static int prevCount = -1;
	int count = 0;
	// Note: refreshComponents ensures that all weak_ptr in m_components are valid, so locking them is guaranteed to produce a valid shared_ptr
	refreshComponents();
	// Ensure we have at least 2 components to handle (needed to avoid the for-loops to attempt to access out of range)
	if (m_components.size() < 2)
	{
		return;
	}
	for (unsigned int i = 0; i < m_components.size() - 1; ++i)
	{
		auto weakCollider1 = m_components[i];
		if (auto collider1 = std::static_pointer_cast<Collider>(weakCollider1.lock()))
		{
			for (unsigned int j = i + 1; j < m_components.size(); ++j)
			{
				auto weakCollider2 = m_components[j];
				if (auto collider2 = std::static_pointer_cast<Collider>(weakCollider2.lock()))
				{
					if (!EngineUtils::ptr_owner_equality(collider1, collider2) && (!collider1->isStatic || !collider2->isStatic) && (!collider1->isTrigger || !collider2->isTrigger) )
					{
						// Actual collider on collider check
						if (hasCollision(collider1.get(), collider2.get())) {
							++count;
						}
					}
				}
			}
		}
	}

	if (prevCount != count)
	{
		prevCount = count;
		printf("Colliders found: %i\n", count);
	}
}

bool CollidersManager::hasCollision(Collider* coll1, Collider* coll2)
{
	bool collisionOccured = false;
	// Cast down the first collider
	if (typeid(CircleCollider) == typeid(*coll1))
	{
		auto castedColl1 = static_cast<CircleCollider*>(coll1);

		if (typeid(CircleCollider) == typeid(*coll2))
		{
			auto castedColl2 = static_cast<CircleCollider*>(coll2);
			collisionOccured = hasCollision(*castedColl1, *castedColl2);
		}
		else if (typeid(RectangleCollider) == typeid(*coll2))
		{
			auto castedColl2 = static_cast<RectangleCollider*>(coll2);
			collisionOccured = hasCollision(*castedColl1, *castedColl2);
		}
	}
	else if (typeid(RectangleCollider) == typeid(*coll1))
	{
		auto castedColl1 = static_cast<RectangleCollider*>(coll1);

		if (typeid(CircleCollider) == typeid(*coll2))
		{
			auto castedColl2 = static_cast<CircleCollider*>(coll2);
			collisionOccured = hasCollision(*castedColl1, *castedColl2);
		}
		else if (typeid(RectangleCollider) == typeid(*coll2))
		{
			auto castedColl2 = static_cast<RectangleCollider*>(coll2);
			collisionOccured = hasCollision(*castedColl1, *castedColl2);
		}
	}

	if (collisionOccured)
	{
		informCollision(coll1, coll2);
	}
	return collisionOccured;
}

bool CollidersManager::hasCollision(CircleCollider & circColl1, CircleCollider & circColl2)
{
	Vector2 pos1 = circColl1.getWorldPosition();

	Vector2 pos2 = circColl2.getWorldPosition();

	double penetrationDistance = circColl1.radius + circColl2.radius - Vector2::distance(pos1, pos2);

	if (penetrationDistance > MinPenetration)
	{
		printf("Circ on Circ: contact: %f\n", penetrationDistance);
		resolveCollision(circColl1, pos1, circColl2, pos2, penetrationDistance);
		return true;
	}

	return false;
}

bool CollidersManager::hasCollision(RectangleCollider & rectColl1, RectangleCollider & rectColl2)
{
	// rectColl1
	Vector2 pos1 = rectColl1.getWorldPosition();

	double xMin1 = pos1.x - rectColl1.size.x / 2;
	double xMax1 = xMin1 + rectColl1.size.x;
	double yMin1 = pos1.y - rectColl1.size.y / 2;
	double yMax1 = yMin1 + rectColl1.size.y;

	// rectColl2
	Vector2 pos2 = rectColl2.getWorldPosition();

	double xMin2 = pos2.x - rectColl2.size.x / 2;
	double xMax2 = xMin2 + rectColl2.size.x;
	double yMin2 = pos2.y - rectColl2.size.y / 2;
	double yMax2 = yMin2 + rectColl2.size.y;

	// penetration calculation
	double xPenetration = fmin(xMax1, xMax2) - fmax(xMin1, xMin2);
	double yPenetration = fmin(yMax1, yMax2) - fmax(yMin1, yMin2);

	if (xPenetration > MinPenetration && yPenetration > MinPenetration)
	{
		printf("Rect on Rect: contanct x:%f, y:%f\n", xPenetration, yPenetration);
		resolveCollision(rectColl1, pos1, rectColl2, pos2, xPenetration, yPenetration);
		return true;
	}

	return false;
}

bool CollidersManager::hasCollision(CircleCollider & circColl, RectangleCollider & rectColl)
{
	// circColl
	Vector2 circPos = circColl.getWorldPosition();

	// rectColl
	Vector2 rectPos = rectColl.getWorldPosition();

	Vector2 closestPointFromPointToRect = EngineUtils::closestPointOnOrientedRectFromPoint(rectPos, rectColl.size, circPos);

	double penetrationDistance = 0;
	Vector2 penetrationVector;
	if (EngineUtils::isPointInRect(rectPos, rectColl.size, circPos))
	{
		penetrationVector = closestPointFromPointToRect - circPos;
		penetrationDistance = circColl.radius + penetrationVector.getLength();
	}
	else
	{
		penetrationVector = circPos - closestPointFromPointToRect;
		penetrationDistance = circColl.radius - penetrationVector.getLength();
	}
	penetrationVector.normalize();
	penetrationVector *= penetrationDistance;
	

	if (penetrationDistance > MinPenetration)
	{
		printf("Circ on Rect: contact: %f\n", penetrationDistance);
		resolveCollision(circColl, circPos, rectColl, rectPos, penetrationVector);
		return true;
	}

	return false;
}

bool CollidersManager::hasCollision(RectangleCollider & rectColl, CircleCollider & circColl)
{
	return hasCollision(circColl, rectColl);
}

void CollidersManager::resolveCollision(CircleCollider& circColl1, const Vector2& pos1, CircleCollider& circColl2, const Vector2& pos2, double penetrationDistance)
{
	// First, get the vector to move circColl1 away from circColl2
	Vector2 moveVector = (pos1 - pos2).normalized() * penetrationDistance;

	// Fix for complete overlap (just push along y axis)
	if (moveVector.x == 0 && moveVector.y == 0) {
		moveVector.y = penetrationDistance;
	}

	// Now, define which rectColl has to move (see isStatic) and move it
	if (!circColl1.isStatic && circColl2.isStatic)
	{
		// Only circColl1's gameObject is pushed
		Vector2 targetPos = pos1 + moveVector - circColl1.offset;
		circColl1.gameObject()->transform.setWorldPosition(targetPos);
	}
	else if (circColl1.isStatic && !circColl2.isStatic)
	{
		// Only circColl2's gameObject is pushed
		moveVector = -moveVector;	// Invert the vector to clear rectColl2 away from rectColl1
		Vector2 targetPos = pos2 + moveVector - circColl2.offset;
		circColl2.gameObject()->transform.setWorldPosition(targetPos);
	}
	else {	// So neither circColl1, nor circColl2 are static (both can't be static because this function would have never been called
		// Both  circColl1's gameObject and circColl1's gameObject are pushed
		
		// Move circColl1 away
		Vector2 targetPos1 = pos1 + moveVector / 2 - circColl1.offset;
		circColl1.gameObject()->transform.setWorldPosition(targetPos1);
		// Move circColl2 away
		Vector2 targetPos2 = pos2 + -moveVector / 2 - circColl2.offset;
		circColl2.gameObject()->transform.setWorldPosition(targetPos2);
	}
}

void CollidersManager::resolveCollision(RectangleCollider & rectColl1, const Vector2 & pos1, RectangleCollider & rectColl2, const Vector2 & pos2, double xPenetration, double yPenetration)
{
	// First, get the vector to move rectColl1 away from rectColl2
	Vector2 moveVector((pos1.x - pos2.x), (pos1.y - pos2.y));
	if (pos1.x - pos2.x != 0)
	{
		moveVector.x /= abs(pos1.x - pos2.x);
	}
	if (pos1.y - pos2.y != 0)
	{
		moveVector.y /= abs(pos1.y - pos2.y);
	}
	// Next, scale each coordinate to clear the overlap
	moveVector.x *= xPenetration;
	moveVector.y *= yPenetration;
	
	// Now, remove the smallest coordinate
	if (xPenetration <= yPenetration)
	{
		moveVector.y = 0;
	}
	else
	{
		moveVector.x = 0;
	}

	// Fix for complete overlap (just push along y axis)
	if (moveVector.x == 0 && moveVector.y == 0)
	{
		moveVector.x = 0;
		moveVector.y = yPenetration;
	}

	// Now, define which rectColl has to move (see isStatic) and move only in the shortest direction
	if (!rectColl1.isStatic && rectColl2.isStatic)
	{
		// Only rectColl1's gameObject is pushed
		Vector2 targetPos = pos1 + moveVector - rectColl1.offset;
		rectColl1.gameObject()->transform.setWorldPosition(targetPos);
	}
	else if (rectColl1.isStatic && !rectColl2.isStatic)
	{
		// Only rectColl2's gameObject is pushed
		moveVector = -moveVector;	// Invert the vector to clear rectColl2 away from rectColl1
		Vector2 targetPos = pos2 + moveVector - rectColl2.offset;
		rectColl2.gameObject()->transform.setWorldPosition(targetPos);
	}
	else {	// So neither rectColl1, nor rectColl2 are static (both can't be static because this function would have never been called
		// Both  rectColl1's gameObject and rectColl1's gameObject are pushed

		// Move rectColl1 away
		Vector2 targetPos1 = pos1 + moveVector / 2 - rectColl1.offset;
		rectColl1.gameObject()->transform.setWorldPosition(targetPos1);
		// Move rectColl2 away
		Vector2 targetPos2 = pos2 + -moveVector / 2 - rectColl2.offset;
		rectColl2.gameObject()->transform.setWorldPosition(targetPos2);
	}
}

void CollidersManager::resolveCollision(CircleCollider & circColl, const Vector2 & pos1, RectangleCollider & rectColl, const Vector2 & pos2, const Vector2 & penetrationVector)
{
	// Define which collider has to move (see isStatic) and move using the penetrationVector
	if (!circColl.isStatic && rectColl.isStatic)
	{
		// Only circColl's gameObject is pushed
		Vector2 targetPos = pos1 + penetrationVector - circColl.offset;
		circColl.gameObject()->transform.setWorldPosition(targetPos);
	}
	else if (circColl.isStatic && !rectColl.isStatic)
	{
		// Only rectColl's gameObject is pushed
		Vector2 targetPos = pos2 + -penetrationVector - rectColl.offset;
		rectColl.gameObject()->transform.setWorldPosition(targetPos);
	}
	else {	// So neither circColl, nor rectColl are static (both can't be static because this function would have never been called
			// Both  circColl's gameObject and rectColl's gameObject are pushed

			// Move rectColl1 away
		Vector2 targetPos1 = pos1 + penetrationVector / 2 - circColl.offset;
		circColl.gameObject()->transform.setWorldPosition(targetPos1);
		// Move rectColl2 away
		Vector2 targetPos2 = pos2 + -penetrationVector / 2 - rectColl.offset;
		rectColl.gameObject()->transform.setWorldPosition(targetPos2);
	}

}

void CollidersManager::informCollision(Collider * coll1, Collider * coll2)
{
	printf("GO_%i and GO_%i have collided!\n", coll1->gameObject()->m_id, coll2->gameObject()->m_id);
}
