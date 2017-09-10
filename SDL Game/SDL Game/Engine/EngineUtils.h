#pragma once

#include <memory>
#include <vector>


template <typename T, typename U>
bool ptr_owner_equality(std::weak_ptr<T> wp1, std::weak_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T, typename U>
bool ptr_owner_equality(std::shared_ptr<T> wp1, std::shared_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T, typename U>
bool ptr_owner_equality(std::shared_ptr<T> wp1, std::weak_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T, typename U>
bool ptr_owner_equality(std::weak_ptr<T> wp1, std::shared_ptr<U> wp2)
{
	return !wp1.owner_before(wp2) && !wp2.owner_before(wp1);
}


template <typename T>
int indexOf(std::vector<T> vector, T element)
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
int indexOf(std::vector<std::weak_ptr<T>> vector, std::weak_ptr<T> element)
{
	auto iterator = vector.begin();

	for (; iterator != vector.end() ; ++iterator)
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

