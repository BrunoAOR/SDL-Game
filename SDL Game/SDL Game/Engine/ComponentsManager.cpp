#include "ComponentsManager.h"

#include "ComponentManager.h"
#include "BehavioursManager.h"

std::vector<std::shared_ptr<ComponentManager>> ComponentsManager::componentManagers;

ComponentsManager::ComponentsManager()
{
}

bool ComponentsManager::sendToManager(std::weak_ptr<Component> component)
{
	for (auto compManager : componentManagers)
	{
		if (compManager->subscribeComponent(component))
		{
			return true;
		}
	}
	return false;
}


ComponentsManager::~ComponentsManager()
{
}

void ComponentsManager::init()
{
	componentManagers.push_back(std::unique_ptr<BehavioursManager>(new BehavioursManager()));
}

void ComponentsManager::close()
{
	componentManagers.clear();
}

void ComponentsManager::update()
{
	for (auto compManager : componentManagers)
	{
		compManager->update();
	}
}
