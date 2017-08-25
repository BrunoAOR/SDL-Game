#pragma once

#include <vector>
#include "Engine\Behaviour.h"

class GameObject;


class Spawner :
	public Behaviour
{
public:
	Spawner(GameObject* parentGameObject);

	// Inherited via Behaviour
	virtual void update() override;

private:
	std::vector<GameObject*> spawned;
	int xPos;
	int spawnOffset;

	void createCrosshair();
	void removeCrosshair(GameObject* gameObject);
};
