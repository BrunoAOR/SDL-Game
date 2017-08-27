#pragma once

#include <string>
#include <vector>

#include "Transform.h"

class Texture;
class Behaviour;


class GameObject final
{
	friend class GameObjectsManager;
public:
	Transform transform;
	Texture* texture;
	//Behaviour* behaviour;
	
	~GameObject();

	bool addTexture(std::string path);
	void removeTexture();

	template<typename T>
	bool addBehaviour();
	void removeBehaviour(Behaviour* behaviour);

	void setActive(bool activeState);
	bool isActive();

	static GameObject* createNew();
	static void destroy(GameObject* gameObject);

private:
	// The renderer associated with this texture
	std::vector<Behaviour *> m_behaviours;
	std::vector<Behaviour *> m_behavioursToAdd;
	std::vector<Behaviour *> m_behavioursToRemove;
	bool m_isActive;
	bool m_isUpdating;

	GameObject();

	void doAddBehaviour(Behaviour* behaviour);
	void doRemoveBehaviour(Behaviour* behaviour);
	void refreshBehaviours();
};


template<typename T>
inline bool GameObject::addBehaviour()
{
	if (std::is_base_of<Behaviour, T>::value)
	{
		T* behaviour = new T();
		behaviour->m_gameObject = this;
		if (m_isUpdating)
		{
			m_behavioursToAdd.push_back(behaviour);
		}
		else
		{
			doAddBehaviour(behaviour);
		}
		return true;
	}
	else
	{
		printf("Error, can't attach selected class as a behaviour!");
		return false;
	}
}