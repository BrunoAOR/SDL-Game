#pragma once

#include <string>
#include <vector>

#include "Transform.h"

class Texture;
class Behaviour;


class GameObject
{
public:
	Transform transform;
	Texture* texture;
	//Behaviour* behaviour;
	
	GameObject();
	~GameObject();

	bool addTexture(std::string path);
	void removeTexture();

	void addBehaviour(Behaviour* behaviour);
	void removeBehaviour(Behaviour* behaviour);

	template<typename T>
	bool addBehaviour();

private:
	// The renderer associated with this texture
	std::vector<Behaviour *> behaviours;
};


template<typename T>
bool GameObject::addBehaviour() {
	// Success flag
	bool success = true;

	if (std::is_base_of<Behaviour, T>::value) {
		T* behaviour = new T(this);
		behaviours.push_back(behaviour);
	}
	else {
		success = false;
		printf("Error, can't attach selected class as a behaviour!");
	}

	return success;
}
