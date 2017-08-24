#include "Vector2.h"
#include <cmath>

float Vector2::getLength()
{
	return sqrtf(getLengthSquared());
}

float Vector2::getLengthSquared()
{
	return x * x + y * y;
}