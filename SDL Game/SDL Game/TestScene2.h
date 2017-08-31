#pragma once
#include "D:\Documents\Visual Studio 2017\Projects\SDL-Game\SDL Game\SDL Game\Engine\Scene.h"
class TestScene2 :
	public Scene
{
public:
	// Inherited via Scene
	virtual bool load() override;
	virtual void unload() override;
};

