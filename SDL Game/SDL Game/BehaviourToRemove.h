#pragma once
#include "Engine\Behaviour.h"
class BehaviourToRemove :
	public Behaviour
{
public:
	~BehaviourToRemove();
	// Inherited via Behaviour
	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;
};

