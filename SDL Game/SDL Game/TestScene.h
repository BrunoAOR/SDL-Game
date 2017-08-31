#pragma once
#include "Engine\Scene.h"


class TestScene :
	public Scene
{
public:
	// Inherited via Scene
	virtual bool load() override;
	virtual void unload() override;
};

