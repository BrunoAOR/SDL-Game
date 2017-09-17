#pragma once

#include<memory>

class GameObject;

class Component
{
public:
	friend class ComponentsManager;

	Component();
	virtual ~Component() = 0;
	
	std::shared_ptr<GameObject> gameObject();

private:
	// TESTING FIELDS START
	static int s_alive;
	static int s_nextId;
	int m_id;
	// TESTING FIELDS END

	std::weak_ptr<GameObject> m_gameObject;
};
