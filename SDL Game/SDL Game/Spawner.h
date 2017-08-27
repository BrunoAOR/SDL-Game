#pragma once

#include <vector>
#include "Engine\Behaviour.h"

class GameObject;


class Spawner :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	// Inherited via Behaviour
	virtual void update() override;

private:
	std::vector<GameObject*> m_spawned;
	int m_xPos;
	int m_spawnOffset;

	void createCrosshair();
	void removeCrosshair(GameObject* gameObject);
};
