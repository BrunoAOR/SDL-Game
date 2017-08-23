#pragma once

#include "Behaviour.h"

class GameObject;


class Crosshair :
	public Behaviour
{
public:
	Crosshair(GameObject* parentGameObject);
	~Crosshair();

	void update();

private:
	int alpha;
};

