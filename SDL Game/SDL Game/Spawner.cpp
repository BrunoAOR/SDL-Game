#include "Spawner.h"

#include "Engine/EngineUtils.h"
#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "SpawnedCrosshair.h"


void Spawner::start()
{
	m_xPos = 80;
	m_spawnOffset = 80;
}


void Spawner::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_Q))
	{
		createCrosshair();
	}
	if (Input::getKeyDown(SDL_SCANCODE_W))
	{
		if (m_spawned.size() != 0)
		{
			removeCrosshair(m_spawned.at(0));
		}
	}
}


void Spawner::createCrosshair()
{
	auto weakCrosshairGO = GameObject::createNew();
	auto crosshairGO = weakCrosshairGO.lock();
	if (crosshairGO)
	{
		crosshairGO->transform.position = { (float)m_xPos, 80 };
		crosshairGO->addComponent<SpawnedCrosshair>();
		m_xPos += m_spawnOffset;
		crosshairGO->addTexture("assets/Crosshair.png");
		m_spawned.push_back(crosshairGO);
	}
	
}


void Spawner::removeCrosshair(std::weak_ptr<GameObject> gameObject)
{
	int index = indexOf(m_spawned, gameObject);
	if (index != -1)
	{
		auto go = m_spawned.at(index);
		m_spawned.erase(m_spawned.begin() + index);
		GameObject::destroy(go);
	}
}
