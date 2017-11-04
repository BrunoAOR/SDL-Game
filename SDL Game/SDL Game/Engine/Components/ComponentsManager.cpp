#include "ComponentsManager.h"

#include "Engine/Components/Behaviours/BehavioursManager.h"
#include "Engine/Components/Colliders/CollidersManager.h"
#include "Engine/Components/Renderers/RenderersManager.h"


ComponentsManager::ComponentsManager()
{
}


ComponentsManager::~ComponentsManager()
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


bool ComponentsManager::init()
{
	// Success flag
	bool success = true;

	componentManagers.push_back(std::unique_ptr<BehavioursManager>(new BehavioursManager()));
	componentManagers.push_back(std::unique_ptr<CollidersManager>(new CollidersManager()));
	componentManagers.push_back(std::unique_ptr<RenderersManager>(new RenderersManager()));
	for (auto compManager : componentManagers)
	{
		success &= compManager->init();
	}
	return success;
}


void ComponentsManager::close()
{
	for (auto compManager : componentManagers)
	{
		compManager->close();
	}
	componentManagers.clear();
}


void ComponentsManager::update()
{
	for (auto compManager : componentManagers)
	{
		compManager->update();
	}
}
