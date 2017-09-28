#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"

#include <memory>

class Sprite;


class Crosshair :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

private:
	int m_alpha;
	std::weak_ptr<Sprite> sprite;
};
