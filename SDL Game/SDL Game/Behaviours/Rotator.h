#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"


class Rotator :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void update() override;

private:
	double rotStep = 5;
};

