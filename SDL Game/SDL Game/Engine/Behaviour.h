#pragma once

class GameObject;


class Behaviour
{
public:
	GameObject* gameObject;

	Behaviour(GameObject* parentGameObject);
	virtual ~Behaviour();
	virtual void update() = 0;
	
};
