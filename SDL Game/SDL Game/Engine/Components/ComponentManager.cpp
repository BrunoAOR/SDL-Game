#include "ComponentManager.h"

#include "Engine/EngineUtils.h"


ComponentManager::ComponentManager()
{
}


ComponentManager::~ComponentManager()
{
}


bool ComponentManager::subscribeComponent(std::weak_ptr<Component> component)
{
	// If component is not already in the components-to-subscribe list, add it
	if (canManage(component) && EngineUtils::indexOf(m_componentsToSubscribe, component) == -1)
	{
		m_componentsToSubscribe.push_back(component);
		return true;
	}
	return false;
}


bool ComponentManager::unsubscribeComponent(std::weak_ptr<Component> component)
{
	// If component is not already in the components-to-unsubscribe list, add it
	if (EngineUtils::indexOf(m_componentsToSubscribe, component) == -1)
	{
		m_componentsToUnsubscribe.push_back(component);
		return true;
	}
	return false;
}


void ComponentManager::refreshComponents()
{
	for (auto component : m_components)
	{
		if (component.expired())
		{
			unsubscribeComponent(component);
		}
	}

	// Unsubscribe components
	for (auto component : m_componentsToUnsubscribe)
	{
		doUnsubscribe(component);
	}
	m_componentsToUnsubscribe.clear();

	// Subscribe components
	for (auto component : m_componentsToSubscribe)
	{
		doSubscribe(component);
	}
	m_componentsToSubscribe.clear();
}


void ComponentManager::doSubscribe(std::weak_ptr<Component> component)
{
	// If component is not already in the components list, add it
	if (EngineUtils::indexOf(m_components, component) == -1)
	{
		m_components.push_back(component);
	}
}


void ComponentManager::doUnsubscribe(std::weak_ptr<Component> component)
{
	// If component is in the components list, then remove it
	int index = EngineUtils::indexOf(m_components, component);
	if (index != -1)
	{
		m_components.erase(m_components.begin() + index);
	}
}
