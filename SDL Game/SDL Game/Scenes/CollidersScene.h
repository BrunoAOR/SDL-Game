#pragma once
#include "Engine\Scene.h"


class CollidersScene :
	public Scene
{
public:
	// Inherited via Scene
	virtual bool load() override;
	virtual void unload() override;
};

