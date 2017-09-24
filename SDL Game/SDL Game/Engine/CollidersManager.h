#pragma once

#include "ComponentManager.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"

class CollidersManager final :
	public ComponentManager
{
	friend class ComponentsManager;

public:
	~CollidersManager();
	// Inherited via ComponentManager
	virtual void update() override;
	virtual bool canManage(std::weak_ptr<Component> component) override;

private:
	CollidersManager();

	static const double MinPenetration;

	bool hasCollision(Collider* coll1, Collider* coll2);
	bool hasCollision(CircleCollider& circColl1, CircleCollider& circColl2);
	bool hasCollision(RectangleCollider& rectColl1, RectangleCollider& rectColl2);
	bool hasCollision(CircleCollider& circColl, RectangleCollider& rectColl);
	bool hasCollision(RectangleCollider& rectColl, CircleCollider& circColl);

	void resolveCollision(CircleCollider& circColl1, const Vector2& pos1, CircleCollider& circColl2, const Vector2& pos2, double penetrationDistance);
	void resolveCollision(RectangleCollider& rectColl1, RectangleCollider& rectColl2, Vector2& penetrationVector);
	void resolveCollision(CircleCollider& circColl, const Vector2& pos1, RectangleCollider& rectColl, const Vector2& pos2, const Vector2& penetrationVector);

	void informCollision(Collider* coll1, Collider* coll2);
};

