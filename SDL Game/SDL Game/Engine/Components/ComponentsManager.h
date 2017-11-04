#pragma once

#include <memory>
#include <vector>
#include "Engine/Components/Component.h"

class GameObject;
class ComponentManager;


class ComponentsManager final
{
public:
	ComponentsManager();
	~ComponentsManager();
	
	bool init();
	void close();

	void update();

	template <class T>
	std::shared_ptr<T> createNew(std::weak_ptr<GameObject> goWeakPtr);

private:
	std::vector<std::shared_ptr<ComponentManager>> componentManagers;
	bool sendToManager(std::weak_ptr<Component> component);
};

template<class T>
inline std::shared_ptr<T> ComponentsManager::createNew(std::weak_ptr<GameObject> goWeakPtr)
{
	if (!std::is_base_of<Component, T>::value || std::is_abstract<T>::value)
	{
		return std::shared_ptr<T>();
	}
	else
	{
		// Special case: A GameObject may only contain 1 Transform (added after GameObject instantiation
		if (typeid(T) == typeid(Transform) && !(goWeakPtr.lock()->getComponent<Transform>().expired()))
		{
			return std::shared_ptr<T>();
		}
		else
		{
			auto component = std::make_shared<T>();
			component->m_gameObject = goWeakPtr;

			if (typeid(T) != typeid(Transform) && !sendToManager(component))
			{
				component.reset();
			}
			return component;
		}
	}
}
