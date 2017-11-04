#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Engine/Engine.h"
#include "Engine/Components/ComponentsManager.h"

class Component;
class Transform;


class GameObject final
{
	friend class GameObjectsManager;
public:
	std::weak_ptr<Transform> transform;
	
	GameObject();
	~GameObject();

	// Components related
	template<typename T>
	std::weak_ptr<T> addComponent();
	void removeComponent(std::weak_ptr<Component> component);
	template<typename T>
	std::weak_ptr<T> getComponent();
	template<typename T>
	std::vector<std::weak_ptr<T>> getComponents();

	// On/Off switch
	void setActive(bool activeState);
	bool isActive();

	// Creation and destruction related
	static std::weak_ptr<GameObject> createNew();
	static void destroy(std::weak_ptr<GameObject> gameObject);

	// TESTING FIELDS START
	int m_id;
	// TESTING FIELDS END

private:
	// TESTING FIELDS START
	static int s_alive;
	static int s_nextId;
	//int m_id;
	// TESTING FIELDS END

	std::shared_ptr<Transform> m_transform;

	bool m_isActive;
	std::weak_ptr<GameObject> m_self;


	// Components related
	std::vector<std::shared_ptr<Component>> m_components;
	std::vector<std::shared_ptr<Component>> m_componentsToAdd;
	std::vector<std::weak_ptr<Component>> m_componentsToRemove;

	void doAddComponent(std::shared_ptr<Component> component);
	void doRemoveComponent(std::weak_ptr<Component> component);
	void refreshComponents();
};


template<typename T>
inline std::weak_ptr<T> GameObject::addComponent()
{
	std::weak_ptr<T> weakComponent;
	auto component = engine->componentsManager->createNew<T>(m_self);
	if (component)
	{
		m_componentsToAdd.push_back(component);
		weakComponent = component;
	}
	else
	{
		printf("Error, can't attach selected class as a component!\n");
	}
	return weakComponent;
}

template<typename T>
inline std::weak_ptr<T> GameObject::getComponent()
{
	std::weak_ptr<T> weakPtr;
	if (!std::is_base_of<Component, T>::value)
	{
		printf("Error, selected class is not allowed!\n");
	}
	else
	{
		for (auto componentSharedPtr : m_components)
		{
			if (std::dynamic_pointer_cast<T>(componentSharedPtr))
			{
				weakPtr = std::static_pointer_cast<T>(componentSharedPtr);
			}
		}
	}
	return weakPtr;
}


template<typename T>
inline std::vector<std::weak_ptr<T>> GameObject::getComponents()
{
	std::vector<std::weak_ptr<T>> weakPtrVector;
	if (!std::is_base_of<Component, T>::value)
	{
		printf("Error, selected class is not allowed!\n");
	}
	else
	{
		for (auto componentSharedPtr : m_components)
		{
			if (std::dynamic_pointer_cast<T>(componentSharedPtr))
			{
				std::weak_ptr<T> weakPtr = std::static_pointer_cast<T>(componentSharedPtr);
				weakPtrVector.push_back(weakPtr);
			}
		}
	}
	return weakPtrVector;
}
