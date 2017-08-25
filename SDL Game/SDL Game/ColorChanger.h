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

	ColorChanger(GameObject* parentGameObject);
	~ColorChanger();

	// Inherited via Behaviour
	virtual void update() override;
};

