#include "Vector2.h"
#include <cmath>


double Vector2::getLength()
{
	return sqrt(getLengthSquared());
}


double Vector2::getLengthSquared()
{
	return x * x + y * y;
}
