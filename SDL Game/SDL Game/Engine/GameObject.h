#pragma once

#include <string>
#include <vector>

#include "Transform.h"

class Texture;
class Behaviour;


class GameObject final
{
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
	static bool destroy(GameObject* gameObject);

private:
	// The renderer associated with this texture
	std::vector<Behaviour *> m_behaviours;

	GameObject();
	// Whether Behaviour and Rendering should happen for this GameObject
	bool m_isActive;
};


template<typename T>
bool GameObject::addBehaviour()
{
	// Success flag
	bool success = true;

	if (std::is_base_of<Behaviour, T>::value)
	{
		T* behaviour = new T();
		behaviour->m_gameObject = this;
		m_behaviours.push_back(behaviour);
	}
	else
	{
		success = false;
		printf("Error, can't attach selected class as a behaviour!");
	}

	return success;
}
