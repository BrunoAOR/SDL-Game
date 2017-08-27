#pragma once

#include "Engine/Behaviour.h"

class GameObject;


class Crosshair2 :
	public Behaviour
{
public:	
	// Inherited via Behaviour
	virtual void start() override;
	// Inherited via Behaviour
	virtual void update() override;

	const int stepSize = 10;
};
