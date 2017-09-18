#pragma once

#include<memory>

class GameObject;

class Component
{
	friend class ComponentsManager;

public:
	Component();
	virtual ~Component() = 0;
	
	std::shared_ptr<GameObject> gameObject();
	void setActive(bool activeState);
	bool isActive();

private:
	// TESTING FIELDS START
	static int s_alive;
	static int s_nextId;
	int m_id;
	// TESTING FIELDS END

	std::weak_ptr<GameObject> m_gameObject;
	bool m_isActive;
};
