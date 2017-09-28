#pragma once

#include "Engine/Components/Colliders/Collider.h"


class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();

	double radius;
};
