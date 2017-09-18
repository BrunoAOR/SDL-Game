#include "BehavioursManager.h"

#include "Behaviour.h"
#include "GameObject.h"


BehavioursManager::BehavioursManager()
{
}


BehavioursManager::~BehavioursManager()
{
}


bool BehavioursManager::canManage(std::weak_ptr<Component> component)
{
	if (std::dynamic_pointer_cast<Behaviour>(component.lock()))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void BehavioursManager::update()
{
	// Note: refreshComponents ensures that all weak_ptr in m_components are valid, so locking them is guaranteed to produce a valid shared_ptr
	refreshComponents();
	for (auto weakBehaviour : m_components)
	{
		if (auto behaviour = std::static_pointer_cast<Behaviour>(weakBehaviour.lock()))
		{
			// Actual update
			if (!behaviour->m_isAwake)
			{
				behaviour->awake();
				behaviour->m_isAwake = true;
			}
			else if (behaviour->gameObject()->isActive())
			{
				if (!behaviour->m_started) {
					behaviour->start();
					behaviour->m_started = true;
				}
				else
				{
					behaviour->update();
				}
			}
		}	
	}
}
