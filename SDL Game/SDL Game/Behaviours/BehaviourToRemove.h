#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"


class BehaviourToRemove :
	public Behaviour
{
public:
	~BehaviourToRemove();
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;
};

