#pragma once

#include <vector>
#include "Engine/Components/Colliders/Collider.h"
#include "Engine/Vector2.h"


class RectangleCollider :
	public Collider
{
public:
	RectangleCollider();
	~RectangleCollider();

	std::vector<Vector2> getWorldCorners();
	std::vector<Vector2> getOuterNormals();

	Vector2 size;

private:
	Vector2 m_cachedWorldPosition;
	double m_cachedRotation;
	std::vector<Vector2> m_worldCorners;
	std::vector<Vector2> m_outerNormals;

	void checkCacheValidity();
};

