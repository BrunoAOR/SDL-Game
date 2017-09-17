#include "BehavioursManager.h"

#include "Behaviour.h"
#include "GameObject.h"


BehavioursManager::BehavioursManager()
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


BehavioursManager::~BehavioursManager()
{
}


void BehavioursManager::update()
{
	refreshComponents();
	for (auto weakBehaviour : m_components)
	{
		auto lockedBehaviour = weakBehaviour.lock();
		if (lockedBehaviour)
		{
			if (auto behaviour = std::static_pointer_cast<Behaviour>(lockedBehaviour))
			{
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
		else
		{
			unsubscribeComponent(weakBehaviour);
		}
	}
}


