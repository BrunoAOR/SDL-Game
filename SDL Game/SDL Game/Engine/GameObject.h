#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Transform.h"
#include "ComponentsManager.h"

class Texture;
class Component;
class Behaviour;


class GameObject final
{
	friend class GameObjectsManager;
public:
	std::weak_ptr<Transform> transform;

	Texture* texture;
	
	GameObject();
	~GameObject();

	// Texture related
	bool addTexture(std::string path);
	void removeTexture();

	// Components related
	template<typename T>
	std::weak_ptr<T> addComponent();
	void removeComponent(std::weak_ptr<Component> component);
	template<typename T>
	std::weak_ptr<T> getComponent();

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


	// Components/Behaviours related
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
	auto component = ComponentsManager::createNew<T>(m_self);
	if (component)
	{
		m_componentsToAdd.push_back(component);
		weakComponent = component;
	}
	else
	{
		printf("Error, can't attach selected class as a component!");
	}
	return weakComponent;
}

template<typename T>
inline std::weak_ptr<T> GameObject::getComponent()
{
	std::weak_ptr<T> weakPtr;
	if (!std::is_base_of<Component, T>::value || std::is_abstract<T>::value)
	{
		printf("Error, selected class is not allowed!");
	}
	else
	{
		for (auto componentSharedPtr : m_components)
		{
			if (typeid(T) == typeid(*componentSharedPtr))
			{
				weakPtr = std::static_pointer_cast<T>(componentSharedPtr);
			}
		}
	}
	return weakPtr;
}
