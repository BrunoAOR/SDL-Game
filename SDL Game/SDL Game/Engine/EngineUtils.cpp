# include <vector>

template <class T>
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