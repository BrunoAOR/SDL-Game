#pragma once

#include "Engine\Collider.h"
#include "Engine/Vector2.h"


class RectangleCollider :
	public Collider
{
public:
	RectangleCollider();
	~RectangleCollider();

	Vector2 size;
};

