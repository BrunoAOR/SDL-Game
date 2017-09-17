#pragma once

#include "Component.h"

class GameObject;


class Behaviour :
	public Component
{
public:
	friend class BehavioursManager;

	void setActive(bool activeState);
	bool isActive();

	Behaviour();
	virtual ~Behaviour() = 0;

	virtual void awake();
	virtual void start();
	virtual void update();

private:
	bool m_isActive;
	bool m_isAwake;
	bool m_started;
};
