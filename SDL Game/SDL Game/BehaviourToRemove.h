#pragma once
#include "D:\Documents\Visual Studio 2017\Projects\SDL-Game\SDL Game\SDL Game\Engine\Behaviour.h"
class BehaviourToRemove :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

};

