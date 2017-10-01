#include "BehavioursManager.h"

#include "Engine/Components/Behaviours/Behaviour.h"
#include "Engine/Components/ComponentType.h"
#include "Engine/GameObjects/GameObject.h"


BehavioursManager::BehavioursManager()
{
}


BehavioursManager::~BehavioursManager()
{
}


ComponentType BehavioursManager::managedComponentType()
{
	return ComponentType::Behaviour;
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


bool BehavioursManager::init()
{
	return true;
}


void BehavioursManager::close()
{
}


bool BehavioursManager::initializeComponent(std::weak_ptr<Component> component)
{
	return true;
}
