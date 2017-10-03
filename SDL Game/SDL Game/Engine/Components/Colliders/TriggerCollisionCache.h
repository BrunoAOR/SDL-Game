#pragma once

#include <memory>
#include <vector>
class Collider;

using CollidersPair = std::pair<std::weak_ptr<Collider>, std::weak_ptr<Collider>>;
class TriggerCollisionCache final
{
public:
	bool cache(CollidersPair collPair);
	void refresh();

private:
	std::vector<CollidersPair> collPairs;
	std::vector<CollidersPair> registeredCollPairs;
	
	int indexOf(std::vector<CollidersPair> collPairVector, CollidersPair collPair);
};
