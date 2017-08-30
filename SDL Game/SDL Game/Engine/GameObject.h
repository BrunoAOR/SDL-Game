#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Transform.h"
#include "EngineUtils.h"

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

	bool addTexture(std::string path);
	void removeTexture();

	template<typename T>
	bool addComponent();
	void removeComponent(std::weak_ptr<Component> component);
	template<typename T>
	std::weak_ptr<T> getComponent();

	void setActive(bool activeState);
	bool isActive();

	static std::weak_ptr<GameObject> createNew();
	static void destroy(std::weak_ptr<GameObject> gameObject);

private:
	static int m_nextId;
	int m_id;
	bool m_isActive;
	std::weak_ptr<GameObject> self;
	std::vector<std::shared_ptr<Component>> m_components;
	std::vector<std::shared_ptr<Component>> m_componentsToAdd;
	std::vector<std::weak_ptr<Component>> m_componentsToRemove;
	std::vector<std::shared_ptr<Behaviour>> m_behaviours;

	void doAddComponent(std::shared_ptr<Component> component);
	void doRemoveComponent(std::weak_ptr<Component> component);
	void refreshComponents();
};


template<typename T>
inline bool GameObject::addComponent()
{
	if (!std::is_base_of<Component, T>::value || std::is_same<Component, T>::value || std::is_same<Behaviour, T>::value)
	{
		printf("Error, can't attach selected class as a component!");
		return false;
	}
	else
	{
		// So T inherits from Component and is NOT a Component or a Behaviour as such
		auto component = std::make_shared<T>();
		component->m_gameObject = self;
		m_componentsToAdd.push_back(component);
		return true;
	}
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
