#include "Spawner.h"

#include "Engine/EngineUtils.cpp"
#include "Engine/Input.h"
#include "Engine/GameObject.h"


Spawner::Spawner(GameObject* parentGameObject) : Behaviour(parentGameObject), xPos(80), spawnOffset(80)
{
	
}


void Spawner::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_Q))
	{
		createCrosshair();
	}
	if (Input::getKeyDown(SDL_SCANCODE_W))
	{
		if (spawned.size() != 0)
		{
			removeCrosshair(spawned.at(0));
		}
	}
}


void Spawner::createCrosshair()
{
	GameObject* crosshairGO = GameObject::createNew();
	crosshairGO->transform.position = { (float)xPos, 80 };
	xPos += spawnOffset;
	crosshairGO->addTexture("assets/Crosshair.png");
	spawned.push_back(crosshairGO);
}


void Spawner::removeCrosshair(GameObject* gameObject)
{
	int index = indexOf(spawned, gameObject);
	if (index != -1)
	{
		GameObject* go = spawned.at(index);
		spawned.erase(spawned.begin() + index);
		GameObject::destroy(go);
	}
}
