#include "Behaviour.h"

#include "BehavioursManager.h"

Behaviour::Behaviour(GameObject* parentGameObject)
{
	gameObject = parentGameObject;
	BehavioursManager::subscribeBehaviour(this);
}


Behaviour::~Behaviour()
{
	BehavioursManager::unsubscribeBehaviour(this);
}
