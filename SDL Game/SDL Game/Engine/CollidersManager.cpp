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
		//printf("Colliders found: %i\n", count);
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
		//informCollision(coll1, coll2);
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
	// First, we get the normals from the rectColls.
	// Only the first 2 normals are needed for each rect, since the other two are the same but in opposite direction
	// Special case: if the rotation of both rectangle is the same, then only the first 2 normals of either rectColl are required
	if (rectColl1.gameObject()->m_id == 1 || rectColl2.gameObject()->m_id == 1) {
		rectColl1.size = rectColl1.size;
	}
	std::vector<Vector2> selectedNormals;
	if (rectColl1.getWorldRotation() == rectColl2.getWorldRotation())
	{
		auto r1Normals = rectColl1.getOuterNormals();
		selectedNormals = { r1Normals[0], r1Normals[1]};
	}
	else
	{
		auto r1Normals = rectColl1.getOuterNormals();
		auto r2Normals = rectColl2.getOuterNormals();
		selectedNormals = { r1Normals[0], r1Normals[1], r2Normals[0], r2Normals[1] };
	}

	// Now we need iterate through the selectedNormals projecting the rects' corners onto the normal and recording the smallest overlap found
	// 1. Get the corners for both rects
	auto r1Corners = rectColl1.getWorldCorners();
	auto r2Corners = rectColl2.getWorldCorners();

	// 2. Create variables to store the smallest overlap vector and direction (stored separate to easily compare the length)
	double minOverlapLength = std::numeric_limits<double>::max();
	Vector2 minOverlapDirection;

	// 3. Now we iterate
	for (unsigned int i = 0; i < selectedNormals.size(); ++i)
	{
		// 1. Get the Normal unit vector
		Vector2 normalUnitVector = selectedNormals[i].normalized();

		// 2. Find the min and max corner projections for r1 and r2
		// For r1
		double r1Min = std::numeric_limits<double>::max();
		double r1Max = std::numeric_limits<double>::lowest();
		// For r2
		double r2Min = std::numeric_limits<double>::max();
		double r2Max = std::numeric_limits<double>::lowest();

		for (int c = 0; c < 4; ++c)
		{
			// r1
			double currentR1Projection = Vector2::dot(r1Corners[c], normalUnitVector);
			
			if (currentR1Projection < r1Min)
			{
				r1Min = currentR1Projection;
			}
			if (currentR1Projection > r1Max)
			{
				r1Max = currentR1Projection;
			}

			// r2
			double currentR2Projection = Vector2::dot(r2Corners[c], normalUnitVector);

			if (currentR2Projection < r2Min)
			{
				r2Min = currentR2Projection;
			}
			if (currentR2Projection > r2Max)
			{
				r2Max = currentR2Projection;
			}
		}

		// 3. Determine if there is an overlap. If there isn't, early exit and return false
		double penetrationDistance = -EngineUtils::getRangesSeparationDistance(r1Min, r1Max, r2Min, r2Max);
		if (penetrationDistance <= MinPenetration)
		{
			// So, no overlap in this axis
			return false;
		}
		// So, there is overlap in this axis. Compare with cached minOverlap (turn projectionSeparation into a possitive value
		else if (penetrationDistance < minOverlapLength)
		{
			minOverlapLength = penetrationDistance;
			minOverlapDirection = normalUnitVector;
		}
		// And now we continue with the next test axis (next normal)
	}

	// If we got here, we have a minOverlapLength and Direction that can be used to resolve the collision
	//printf("Rect on Rect: contanct penetrationDistance:%f\n", minOverlapLength);
	resolveCollision(rectColl1, rectColl2, minOverlapLength * minOverlapDirection);
	return true;
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


void CollidersManager::resolveCollision(RectangleCollider & rectColl1, RectangleCollider & rectColl2, Vector2 & penetrationVector)
{
	Vector2 pos1 = rectColl1.getWorldPosition();
	Vector2 pos2 = rectColl2.getWorldPosition();

	// Ensure penetrationVector is aligned so that r1 is pulled away from r2
	if (Vector2::dot(pos1 - pos2, penetrationVector) < 0)
	{
		// So they point in 'opposite' direction (angle between them is over 90 degrees)
		penetrationVector *= -1;
	}

	// Now, define which rectColl has to move (see isStatic) and move only in the shortest direction
	if (!rectColl1.isStatic && rectColl2.isStatic)
	{
		// Only rectColl1's gameObject is pushed
		Vector2 targetPos = pos1 + penetrationVector - rectColl1.offset;
		rectColl1.gameObject()->transform.setWorldPosition(targetPos);
	}
	else if (rectColl1.isStatic && !rectColl2.isStatic)
	{
		// Only rectColl2's gameObject is pushed
		// Invert the vector to clear rectColl2 away from rectColl1
		Vector2 targetPos = pos2 + -penetrationVector - rectColl2.offset;
		rectColl2.gameObject()->transform.setWorldPosition(targetPos);
	}
	else {	// So neither rectColl1, nor rectColl2 are static (both can't be static because this function would have never been called
		// Both  rectColl1's gameObject and rectColl1's gameObject are pushed

		// Move rectColl1 away
		Vector2 targetPos1 = pos1 + penetrationVector / 2 - rectColl1.offset;
		rectColl1.gameObject()->transform.setWorldPosition(targetPos1);
		// Move rectColl2 away
		Vector2 targetPos2 = pos2 + -penetrationVector / 2 - rectColl2.offset;
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
