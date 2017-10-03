#pragma once

#include "Engine/Components/ComponentManager.h"
#include "Engine/Components/Colliders/TriggerCollisionCache.h"
class Vector2;
class CircleCollider;
class RectangleCollider;


class CollidersManager final :
	public ComponentManager
{
	friend class ComponentsManager;

public:
	~CollidersManager();

private:
	CollidersManager();

	static const double MinPenetration;

	TriggerCollisionCache triggerCollisionCache;

	// Inherited via ComponentManager
	virtual ComponentType managedComponentType() override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(std::weak_ptr<Component> component) override;

	bool checkAndResolveCollision(std::shared_ptr<Collider> coll1, std::shared_ptr<Collider> coll2, bool shouldResolve);
	bool checkAndResolveCollision(CircleCollider& circColl1, CircleCollider& circColl2, bool shouldResolve);
	bool checkAndResolveCollision(RectangleCollider& rectColl1, RectangleCollider& rectColl2, bool shouldResolve);
	bool checkAndResolveCollision(CircleCollider& circColl, RectangleCollider& rectColl, bool shouldResolve);
	bool checkAndResolveCollision(RectangleCollider& rectColl, CircleCollider& circColl, bool shouldResolve);

	bool shouldResolveCollision(std::shared_ptr<Collider> coll1, std::shared_ptr<Collider> coll2);
	void resolveCollision(CircleCollider& circColl1, const Vector2& pos1, CircleCollider& circColl2, const Vector2& pos2, double penetrationDistance);
	void resolveCollision(RectangleCollider& rectColl1, RectangleCollider& rectColl2, Vector2& penetrationVector);
	void resolveCollision(CircleCollider& circColl, RectangleCollider& rectColl, const Vector2& penetrationVector);

	void informCollision(std::shared_ptr<Collider> coll1, std::shared_ptr<Collider> coll2);
};
