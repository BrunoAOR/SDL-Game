#pragma once

#include <vector>
#include "Engine/Collider.h"
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
	Vector2 m_previousWorldPosition;
	double m_previousRotation;
	std::vector<Vector2> m_worldCorners;
	std::vector<Vector2> m_outerNormals;

	void checkCacheValidity();
};

