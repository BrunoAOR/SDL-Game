#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"


class SpawnedCrosshair :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

private:
	bool m_wentRight;
};

