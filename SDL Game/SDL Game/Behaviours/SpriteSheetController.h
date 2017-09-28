#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"

#include <memory>
#include "Engine/Components/Renderers/SpriteSheet.h"


class SpriteSheetController :
	public Behaviour
{
public:
	virtual void start() override;
	virtual void update() override;

private:
	std::weak_ptr<SpriteSheet> spriteSheet;
};

