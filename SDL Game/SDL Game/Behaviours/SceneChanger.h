#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"


class SceneChanger :
	public Behaviour
{
public:	
	// Inherited via Behaviour
	virtual void update() override;
};

