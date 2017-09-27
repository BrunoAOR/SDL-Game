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

	Vector2 getLocalPosition();
	Vector2 getWorldPosition();
	double getWorldRotation();

	Vector2 offset;
	bool isStatic;
	bool isTrigger;
};

