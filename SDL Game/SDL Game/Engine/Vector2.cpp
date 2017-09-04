#include "Vector2.h"
#include <cmath>


Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(double x, double y) : x(x), y(y)
{
}

double Vector2::getLength()
{
	return sqrt(getLengthSquared());
}


double Vector2::getLengthSquared()
{
	return x * x + y * y;
}


Vector2 operator+(Vector2 lhs, const Vector2 & rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}
