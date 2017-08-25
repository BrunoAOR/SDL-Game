#pragma once

#include "Engine/Behaviour.h"

class GameObject;


class Crosshair :
	public Behaviour
{
public:
	Crosshair(GameObject* parentGameObject);

	// Inherited via Behaviour
	virtual void update() override;

private:
	int alpha;
};
