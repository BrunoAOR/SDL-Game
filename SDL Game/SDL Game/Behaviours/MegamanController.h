#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"

#include <memory>

class SpriteSheet;


class MegamanController :
	public Behaviour
{
public:
	virtual void start() override;
	virtual void update() override;

private:
	std::weak_ptr<SpriteSheet> spriteSheet;
	int animationSpeed;
};

