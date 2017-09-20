#pragma once

#include "Component.h"
#include "Vector2.h"


class Collider :
	public Component
{
	friend class CollidersManager;

public:
	Collider();
	virtual ~Collider() = 0;

	Vector2 getWorldPosition();

	Vector2 offset;
	bool isStatic;
	bool isTrigger;
};

