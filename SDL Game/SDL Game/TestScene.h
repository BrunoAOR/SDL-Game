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

private:
	GameObject* m_crosshairGO;
	GameObject* m_crosshair2GO;
	GameObject* m_spawnerGO;
	GameObject* m_coloredGO;
};

