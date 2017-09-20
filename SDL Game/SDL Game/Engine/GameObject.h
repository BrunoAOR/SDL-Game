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
	Transform transform;
	Texture* texture;
	
	GameObject();
	~GameObject();

	// Texture related
	bool addTexture(std::string path);
	void removeTexture();

	// Components/Behaviours related
	template<typename T>
	std::weak_ptr<T> addComponent();
	void removeComponent(std::weak_ptr<Component> component);
	template<typename T>
	std::weak_ptr<T> getComponent();

	// GameObjects hierarchy (parenting) related
	bool setParent(std::weak_ptr<GameObject> parent);
	bool removeParent();

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

	bool m_isActive;
	std::weak_ptr<GameObject> m_self;

	// GameObjects hierarchy related
	std::weak_ptr<GameObject> m_parent;
	std::vector<std::weak_ptr<GameObject>> m_children;

	bool addChild(std::weak_ptr<GameObject> child);
	bool removeChild(std::weak_ptr<GameObject> child);
	bool isGameObjectInChildrenHierarchy(std::weak_ptr<GameObject> gameObject);

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
	if (!std::is_base_of<Component, T>::value || std::is_same<Component, T>::value)
	{
		printf("Error, can't attach selected class as a component!");
	}
	else
	{
		auto component = ComponentsManager::createNew<T>(m_self);
		// So T inherits from Component and is NOT a Component or a Behaviour as such
		if (component)
		{
			m_componentsToAdd.push_back(component);
			weakComponent = component;
		}
	}
	return weakComponent;
}

template<typename T>
inline std::weak_ptr<T> GameObject::getComponent()
{
	std::weak_ptr<T> weakPtr;
	if (!std::is_base_of<Component, T>::value || std::is_same<Component, T>::value || std::is_same<Behaviour, T>::value)
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
