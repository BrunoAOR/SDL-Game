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
	// TESTING FIELDS START
	static int s_alive;
	static int s_nextId;
	int m_id;
	// TESTING FIELDS END

	std::weak_ptr<GameObject> m_gameObject;
};
