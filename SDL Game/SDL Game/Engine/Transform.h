#pragma once

#include "Vector2.h"


struct Transform
{
public:
	Vector2 position = { 0,0 };
	double rotation = 0;
	Vector2 scale = {1, 1};
};
