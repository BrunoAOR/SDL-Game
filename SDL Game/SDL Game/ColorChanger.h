#pragma once
#include "Engine\Behaviour.h"

class GameObject;

class ColorChanger :
	public Behaviour
{
public:
	int color1[3];
	int color2[3];
	bool color1active;

	// Inherited via Behaviour
	virtual void start() override;
	// Inherited via Behaviour
	virtual void update() override;
};

