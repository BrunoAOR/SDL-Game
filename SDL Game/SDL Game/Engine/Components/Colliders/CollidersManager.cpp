#include "CollidersManager.h"

#include <cmath>
#include "Engine/Components/ComponentType.h"
#include "Engine/EngineUtils.h"
#include "Engine/Vector2.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Components/Colliders/CollisionInfo.h"
#include "Engine/Components/Colliders/CircleCollider.h"
#include "Engine/Components/Colliders/RectangleCollider.h"


const double CollidersManager::MinPenetration = 0.01;


CollidersManager::CollidersManager()
{
}


CollidersManager::~CollidersManager()
{
}


ComponentType CollidersManager::managedComponentType()
{
	return ComponentType::Collider;
}


void CollidersManager::update()
{
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
					if (!EngineUtils::ptr_owner_equality(collider1, collider2))
					{
						// Actual collider on collider check
						bool shouldResolve = shouldResolveCollision(collider1, collider2);
						checkAndResolveCollision(collider1, collider2, shouldResolve);
					}
				}
			}
		}
	}

	// Refresh the triggerCollisionCache to call any onTriggerExit methods required
	triggerCollisionCache.refresh();
}


bool CollidersManager::init()
{
	return true;
}


void CollidersManager::close()
{
}


bool CollidersManager::initializeComponent(std::weak_ptr<Component> component)
{
	return true;
}


bool CollidersManager::checkAndResolveCollision(std::shared_ptr<Collider> coll1, std::shared_ptr<Collider> coll2, bool shouldResolve)
{
	if (coll1->isStatic && !coll2->isStatic)
	{
		return false;
	}

	Collider* coll1_rawPtr = coll1.get();
	Collider* coll2_rawPtr = coll2.get();

	bool collisionOccured = false;
	
	if (typeid(CircleCollider) == typeid(*coll1_rawPtr))
	{
		auto castedColl1 = static_cast<CircleCollider*>(coll1_rawPtr);

		if (typeid(CircleCollider) == typeid(*coll2_rawPtr))
		{
			auto castedColl2 = static_cast<CircleCollider*>(coll2_rawPtr);
			collisionOccured = checkAndResolveCollision(*castedColl1, *castedColl2, shouldResolve);
		}
		else if (typeid(RectangleCollider) == typeid(*coll2_rawPtr))
		{
			auto castedColl2 = static_cast<RectangleCollider*>(coll2_rawPtr);
			collisionOccured = checkAndResolveCollision(*castedColl1, *castedColl2, shouldResolve);
		}
	}
	else if (typeid(RectangleCollider) == typeid(*coll1_rawPtr))
	{
		auto castedColl1 = static_cast<RectangleCollider*>(coll1_rawPtr);

		if (typeid(CircleCollider) == typeid(*coll2_rawPtr))
		{
			auto castedColl2 = static_cast<CircleCollider*>(coll2_rawPtr);
			collisionOccured = checkAndResolveCollision(*castedColl1, *castedColl2, shouldResolve);
		}
		else if (typeid(RectangleCollider) == typeid(*coll2_rawPtr))
		{
			auto castedColl2 = static_cast<RectangleCollider*>(coll2_rawPtr);
			collisionOccured = checkAndResolveCollision(*castedColl1, *castedColl2, shouldResolve);
		}
	}

	if (collisionOccured)
	{
		informCollision(coll1, coll2);
	}
	return collisionOccured;
}


bool CollidersManager::checkAndResolveCollision(CircleCollider & circColl1, CircleCollider & circColl2, bool shouldResolve)
{
	Vector2 pos1 = circColl1.getWorldPosition();

	Vector2 pos2 = circColl2.getWorldPosition();

	double penetrationDistance = circColl1.radius + circColl2.radius - Vector2::distance(pos1, pos2);

	if (penetrationDistance > MinPenetration)
	{
		//printf("Circ on Circ: contact: %f\n", penetrationDistance);
		if (shouldResolve)
		{
			resolveCollision(circColl1, pos1, circColl2, pos2, penetrationDistance);
		}
		return true;
	}

	return false;
}


bool CollidersManager::checkAndResolveCollision(RectangleCollider & rectColl1, RectangleCollider & rectColl2, bool shouldResolve)
{
	// First, we get the normals from the rectColls.
	// Only the first 2 normals are needed for each rect, since the other two are the same but in opposite direction
	// Special case: if the rotation of both rectangle is the same, then only the first 2 normals of either rectColl are required
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
	//printf("Rect on Rect: contanct: %f\n", minOverlapLength);
	if (shouldResolve)
	{
		resolveCollision(rectColl1, rectColl2, minOverlapLength * minOverlapDirection);
	}
	return true;
}


bool CollidersManager::checkAndResolveCollision(CircleCollider & circColl, RectangleCollider & rectColl, bool shouldResolve)
{
	// To solve this collision with rotated rectangles, we'll temporarily place the circle as a child of the rectangle.
	// In this way, the rectColl will be axis aligned in the reference system for the circle
	// So locally, the rectangle would be possitioned at its offset and the circle would be positioned at its localPoisiton + offset

	// Store the circ's previous parent and then change to the rect
	auto circTransform = circColl.gameObject()->transform.lock();
	auto originalCircParent = circTransform->getParent();
	circTransform->setParent(rectColl.gameObject()->transform);

	// circColl
	Vector2 localCircPos = circColl.getLocalPosition();

	// rectColl
	Vector2 localRectPos = rectColl.offset;

	Vector2 closestPointFromPointToRect = EngineUtils::closestPointOnOrientedRectFromPoint(localRectPos, rectColl.size, localCircPos);

	double penetrationDistance = 0;
	Vector2 penetrationVector;
	if (EngineUtils::isPointInRect(localRectPos, rectColl.size, localCircPos))
	{
		penetrationVector = closestPointFromPointToRect - localCircPos;
		penetrationDistance = circColl.radius + penetrationVector.getLength();
	}
	else
	{
		penetrationVector = localCircPos - closestPointFromPointToRect;
		penetrationDistance = circColl.radius - penetrationVector.getLength();
	}
	penetrationVector.normalize();
	penetrationVector *= penetrationDistance;
	
	// Now that all calculations are finished, readjust the penetrationVector for world space (rotation)
	double worldRotOfRectSystem = circTransform->localToWorldRotation(0);
	penetrationVector.rotateCCWDegrees(worldRotOfRectSystem);
	// and return the circ's parent to its original parent
	circTransform->setParent(originalCircParent);

	if (penetrationDistance > MinPenetration)
	{
		//printf("Circ on Rect: contact: %f\n", penetrationDistance);
		if (shouldResolve)
		{
			resolveCollision(circColl, rectColl, penetrationVector);
		}
		return true;
	}

	return false;
}


bool CollidersManager::checkAndResolveCollision(RectangleCollider & rectColl, CircleCollider & circColl, bool shouldResolve)
{
	return checkAndResolveCollision(circColl, rectColl, shouldResolve);
}


bool CollidersManager::shouldResolveCollision(std::shared_ptr<Collider> coll1, std::shared_ptr<Collider> coll2)
{
	return !(coll1->isTrigger || coll2->isTrigger);
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
		circColl1.gameObject()->transform.lock()->setWorldPosition(targetPos);
	}
	else if (circColl1.isStatic && !circColl2.isStatic)
	{
		// Only circColl2's gameObject is pushed
		moveVector = -moveVector;	// Invert the vector to clear rectColl2 away from rectColl1
		Vector2 targetPos = pos2 + moveVector - circColl2.offset;
		circColl2.gameObject()->transform.lock()->setWorldPosition(targetPos);
	}
	else {	// So neither circColl1, nor circColl2 are static (both can't be static because this function would have never been called
		// Both  circColl1's gameObject and circColl1's gameObject are pushed
		
		// Move circColl1 away
		Vector2 targetPos1 = pos1 + moveVector / 2 - circColl1.offset;
		circColl1.gameObject()->transform.lock()->setWorldPosition(targetPos1);
		// Move circColl2 away
		Vector2 targetPos2 = pos2 + -moveVector / 2 - circColl2.offset;
		circColl2.gameObject()->transform.lock()->setWorldPosition(targetPos2);
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
		rectColl1.gameObject()->transform.lock()->setWorldPosition(targetPos);
	}
	else if (rectColl1.isStatic && !rectColl2.isStatic)
	{
		// Only rectColl2's gameObject is pushed
		// Invert the vector to clear rectColl2 away from rectColl1
		Vector2 targetPos = pos2 + -penetrationVector - rectColl2.offset;
		rectColl2.gameObject()->transform.lock()->setWorldPosition(targetPos);
	}
	else {	// So neither rectColl1, nor rectColl2 are static (both can't be static because this function would have never been called
		// Both  rectColl1's gameObject and rectColl1's gameObject are pushed

		// Move rectColl1 away
		Vector2 targetPos1 = pos1 + penetrationVector / 2 - rectColl1.offset;
		rectColl1.gameObject()->transform.lock()->setWorldPosition(targetPos1);
		// Move rectColl2 away
		Vector2 targetPos2 = pos2 + -penetrationVector / 2 - rectColl2.offset;
		rectColl2.gameObject()->transform.lock()->setWorldPosition(targetPos2);
	}

}


void CollidersManager::resolveCollision(CircleCollider & circColl, RectangleCollider & rectColl, const Vector2 & penetrationVector)
{
	Vector2 circPos = circColl.getWorldPosition();
	Vector2 rectPos = rectColl.getWorldPosition();

	// Define which collider has to move (see isStatic) and move using the penetrationVector
	if (!circColl.isStatic && rectColl.isStatic)
	{
		// Only circColl's gameObject is pushed
		Vector2 targetPos = circPos + penetrationVector - circColl.offset;
		circColl.gameObject()->transform.lock()->setWorldPosition(targetPos);
	}
	else if (circColl.isStatic && !rectColl.isStatic)
	{
		// Only rectColl's gameObject is pushed
		Vector2 targetPos = rectPos + -penetrationVector - rectColl.offset;
		rectColl.gameObject()->transform.lock()->setWorldPosition(targetPos);
	}
	else {	// So neither circColl, nor rectColl are static (both can't be static because this function would have never been called
			// Both  circColl's gameObject and rectColl's gameObject are pushed

			// Move rectColl1 away
		Vector2 targetPos1 = circPos + penetrationVector / 2 - circColl.offset;
		circColl.gameObject()->transform.lock()->setWorldPosition(targetPos1);
		// Move rectColl2 away
		Vector2 targetPos2 = rectPos + -penetrationVector / 2 - rectColl.offset;
		rectColl.gameObject()->transform.lock()->setWorldPosition(targetPos2);
	}

}


void CollidersManager::informCollision(std::shared_ptr<Collider> coll1, std::shared_ptr<Collider> coll2)
{
	// If non of the colliders are triggers, then the onCollision method should be called
	if (!coll1->isTrigger && !coll2->isTrigger)
	{
		auto go1 = coll1->gameObject();
		auto go2 = coll2->gameObject();
		// Info about cool2 that will be sent to coll1
		{
			auto infoForColl1 = std::make_shared<CollisionInfo>();
			infoForColl1->otherCollider = coll2;
			infoForColl1->otherGameObject = go2;
			coll1->onCollision(infoForColl1);
		}
		// Info about coll1 that will be sent to coll2
		{
			auto infoForColl2 = std::make_shared<CollisionInfo>();
			infoForColl2->otherCollider = coll1;
			infoForColl2->otherGameObject = go1;
			coll2->onCollision(infoForColl2);
		}
	}
	// If either of the colliders (or both) are triggers, then the onTrigger family of methods should be called
	else
	{
		CollidersPair pair = std::make_pair(coll1, coll2);
		if (triggerCollisionCache.cache(pair))
		{
			// If the pair is new, call OnTriggerEnter
			coll1->onTriggerEnter(coll2);
			coll2->onTriggerEnter(coll1);
		}
		else
		{
			// So the pair was already in the cache
			coll1->onTriggerStay(coll2);
			coll2->onTriggerStay(coll1);
		}
	}
	
}
