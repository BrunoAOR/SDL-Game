#pragma once

#include<memory>

class Component
{
public:
	friend class GameObjectsManager;
	friend class GameObject;
	friend class Behaviour;

	Component();
	virtual ~Component();
	
	std::shared_ptr<GameObject> gameObject();

private:
	std::weak_ptr<GameObject> m_gameObject;
};
