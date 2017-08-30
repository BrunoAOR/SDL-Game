#pragma once

#include <memory>
#include <vector>


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
		if ((*iterator).lock() == element.lock())
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

