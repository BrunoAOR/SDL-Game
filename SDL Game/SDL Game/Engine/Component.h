#pragma once


class Component
{
public:
	friend class GameObjectsManager;
	friend class GameObject;
	friend class Behaviour;

	virtual ~Component();
	GameObject * gameObject();

protected:
	
private:
	Component();

	GameObject * m_gameObject;
};

