#pragma once

#include "Engine/Collider.h"
#include "Engine/Vector2.h"


class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();

	double radius;
};
