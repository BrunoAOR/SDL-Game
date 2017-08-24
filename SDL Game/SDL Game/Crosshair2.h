#pragma once

#include "Engine/Behaviour.h"

class GameObject;


class Crosshair2 :
	public Behaviour
{
public:
	Crosshair2(GameObject* parentGameObject);
	~Crosshair2();
	
	// Inherited via Behaviour
	virtual void update() override;

	const int stepSize = 10;
};

