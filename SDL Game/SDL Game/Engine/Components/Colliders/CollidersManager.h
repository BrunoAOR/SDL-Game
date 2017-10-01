#pragma once

#include "Engine/Components/ComponentManager.h"
#include "Engine/Components/Colliders/CircleCollider.h"
#include "Engine/Components/Colliders/RectangleCollider.h"


class CollidersManager final :
	public ComponentManager
{
	friend class ComponentsManager;

public:
	~CollidersManager();

private:
	CollidersManager();

	static const double MinPenetration;

	// Inherited via ComponentManager
	virtual ComponentType managedComponentType() override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(std::weak_ptr<Component> component) override;

	bool hasCollision(Collider* coll1, Collider* coll2);
	bool hasCollision(CircleCollider& circColl1, CircleCollider& circColl2);
	bool hasCollision(RectangleCollider& rectColl1, RectangleCollider& rectColl2);
	bool hasCollision(CircleCollider& circColl, RectangleCollider& rectColl);
	bool hasCollision(RectangleCollider& rectColl, CircleCollider& circColl);

	void resolveCollision(CircleCollider& circColl1, const Vector2& pos1, CircleCollider& circColl2, const Vector2& pos2, double penetrationDistance);
	void resolveCollision(RectangleCollider& rectColl1, RectangleCollider& rectColl2, Vector2& penetrationVector);
	void resolveCollision(CircleCollider& circColl, RectangleCollider& rectColl, const Vector2& penetrationVector);

	void informCollision(Collider* coll1, Collider* coll2);
};
