#pragma once

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
	
	~GameObject();

	bool addTexture(std::string path);
	void removeTexture();

	template<typename T>
	bool addComponent();
	void removeComponent(Component* component);
	template<typename T>
	T* getComponent();

	void setActive(bool activeState);
	bool isActive();

	static GameObject* createNew();
	static void destroy(GameObject* gameObject);

private:
	std::vector<Component *> m_components;
	std::vector<Behaviour *> m_behaviours;
	std::vector<Component *> m_componentsToAdd;
	std::vector<Component *> m_componentsToRemove;
	bool m_isActive;

	GameObject();

	void doAddComponent(Component* component);
	void doRemoveComponent(Component* component);
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
		T* behaviour = new T();
		behaviour->m_gameObject = this;
		m_componentsToAdd.push_back(behaviour);
		return true;
	}
}

template<typename T>
inline T * GameObject::getComponent()
{
	if (!std::is_base_of<Component, T>::value || std::is_same<Component, T>::value || std::is_same<Behaviour, T>::value)
	{
		printf("Error, selected class is not allowed!");
	}
	else
	{
		for (Component* component : m_components)
		{
			if (T* castedComponent = dynamic_cast<T*>(component))
			{
				return castedComponent;
			}
		}
	}
	return nullptr;
}
