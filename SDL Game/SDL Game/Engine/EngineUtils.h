#pragma once

#include <memory>
#include <vector>
#include "Engine/Vector2.h"


class EngineUtils
{
public:
	static bool inRange(double value, double a, double b);
	static double clamp(double value, double a, double b);
	static bool isPointInRect(const Vector2& rectCenter, const Vector2& rectSize, const Vector2& point);
	static Vector2 closestPointOnOrientedRectFromPoint(const Vector2& rectCenter, const Vector2& rectSize, const Vector2& point);

	template <typename T, typename U>
	static bool ptr_owner_equality(std::weak_ptr<T> wp1, std::weak_ptr<U> wp2);
	template <typename T, typename U>
	static bool ptr_owner_equality(std::shared_ptr<T> wp1, std::shared_ptr<U> wp2);
	template <typename T, typename U>
	static bool ptr_owner_equality(std::shared_ptr<T> wp1, std::weak_ptr<U> wp2);
	template <typename T, typename U>
	static bool ptr_owner_equality(std::weak_ptr<T> wp1, std::shared_ptr<U> wp2);
	template <typename T>
	static int indexOf(std::vector<T> vector, T element);
	template <typename T>
	static int indexOf(std::vector<std::weak_ptr<T>> vector, std::weak_ptr<T> element);

private:
	EngineUtils();
};




template <typename T, typename U>
bool EngineUtils::ptr_owner_equality(std::weak_ptr<T> wp1, std::weak_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T, typename U>
bool EngineUtils::ptr_owner_equality(std::shared_ptr<T> wp1, std::shared_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T, typename U>
bool EngineUtils::ptr_owner_equality(std::shared_ptr<T> wp1, std::weak_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T, typename U>
bool EngineUtils::ptr_owner_equality(std::weak_ptr<T> wp1, std::shared_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T>
int EngineUtils::indexOf(std::vector<T> vector, T element)
{
	auto iterator = std::find(vector.begin(), vector.end(), element);

	if (iterator == vector.end())
	{
		return -1;
	}
	else
	{
		return std::distance(vector.begin(), iterator);
	}
}


template <typename T>
int EngineUtils::indexOf(std::vector<std::weak_ptr<T>> vector, std::weak_ptr<T> element)
{
	auto iterator = vector.begin();

	for (; iterator != vector.end(); ++iterator)
	{
		if (ptr_owner_equality(*iterator, element))
		{
			break;
		}
	}

	if (iterator == vector.end())
	{
		return -1;
	}
	else
	{
		return std::distance(vector.begin(), iterator);
	}
}