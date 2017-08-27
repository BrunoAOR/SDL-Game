#include "BehavioursManager.h"

#include "EngineUtils.cpp"
#include "Behaviour.h"
#include "GameObject.h"


std::vector<Behaviour*> BehavioursManager::behaviours;

BehavioursManager::BehavioursManager()
{
}


void BehavioursManager::update()
{
	for (Behaviour* b : behaviours)
	{
		if (b->gameObject()->isActive())
		{
			if (!b->m_started) {
				b->start();
				b->m_started = true;
			}
			else
			{
				b->update();
			}
		}
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
