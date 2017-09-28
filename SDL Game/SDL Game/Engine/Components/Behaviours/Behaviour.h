#pragma once

#include "Engine/Components/Component.h"


class Behaviour :
	public Component
{
	friend class BehavioursManager;

public:	
	Behaviour();
	virtual ~Behaviour() = 0;

	virtual void awake();
	virtual void start();
	virtual void update();

private:
	bool m_isAwake;
	bool m_started;
};
