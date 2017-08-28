#pragma once

#include "Engine/Behaviour.h"

class GameObject;


class Crosshair :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void awake() override;
	virtual void start() override;
	virtual void update() override;

private:
	int m_alpha;
};
