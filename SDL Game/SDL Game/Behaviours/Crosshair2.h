#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"


class Crosshair2 :
	public Behaviour
{
public:	
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

	const int stepSize = 10;
	double angle;
};
