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
	bool hasCrosshair;

	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;
};
