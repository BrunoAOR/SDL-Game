#pragma once


class Vector2
{
public:
	Vector2();
	Vector2(double x, double y);

	double getLength();
	double getLengthSquared();

	friend Vector2 operator+ (Vector2 lhs, const Vector2& rhs);

	double x;
	double y;
};
