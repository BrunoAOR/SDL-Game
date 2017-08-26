#pragma once
#include "Engine\Scene.h"

class GameObject;


class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

	// Inherited via Scene
	virtual bool load() override;
	virtual void unload() override;
};

