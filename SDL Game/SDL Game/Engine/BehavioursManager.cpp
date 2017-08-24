#include "BehavioursManager.h"

#include "EngineUtils.cpp"
#include "Behaviour.h"

std::vector<Behaviour*> BehavioursManager::behaviours;

BehavioursManager::BehavioursManager()
{
}


void BehavioursManager::update()
{
	for (Behaviour* b : behaviours)
	{
		b->update();
	}
}

void BehavioursManager::subscribeBehaviour(Behaviour * behaviour)
{
	if (indexOf(behaviours, behaviour) == -1) {
		// So, the behaviour hasn't been previously added
		behaviours.push_back(behaviour);
	}
}

void BehavioursManager::unsubscribeBehaviour(Behaviour * behaviour)
{
	int index = indexOf(behaviours, behaviour);
	if (index != -1) {
		// So, the behaviour is in the behaviours vector
		behaviours.erase(behaviours.begin() + index);
	}
}

