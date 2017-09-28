#pragma once

#include "Engine/Components/Behaviours/Behaviour.h"

#include <memory>
#include <vector>

class GameObject;


class Spawner :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

private:
	std::vector<std::weak_ptr<GameObject>> m_spawned;
	int m_xPos;
	int m_spawnOffset;

	void createCrosshair();
	void removeCrosshair(std::weak_ptr<GameObject> gameObject);
};
