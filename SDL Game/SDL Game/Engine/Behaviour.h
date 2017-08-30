#pragma once

#include "Component.h"

class GameObject;


class Behaviour :
	public Component
{
public:
	friend class GameObjectsManager;
	friend class GameObject;

	void setActive(bool activeState);
	bool isActive();

	Behaviour();
	virtual ~Behaviour();

	virtual void awake() = 0;
	virtual void start() = 0;
	virtual void update() = 0;

private:
	bool m_isActive;
	bool m_started;
};
