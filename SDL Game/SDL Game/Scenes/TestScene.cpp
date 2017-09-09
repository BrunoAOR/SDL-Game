#include "TestScene.h"

#include <memory>

#include "Engine/GameObject.h"
#include "Engine/constants.h"
#include "Engine/Texture.h"

#include "Behaviours/Crosshair.h"
#include "Behaviours./Crosshair2.h"
#include "Behaviours/Spawner.h"
#include "Behaviours./ColorChanger.h"
#include "Behaviours/BehaviourToRemove.h"
#include "Behaviours/SceneChanger.h"


bool TestScene::load()
{
	// Loading success flag
	bool success = true;

	// Load gameobjects
	std::weak_ptr<GameObject> weakSpawnerGO;
	std::weak_ptr<GameObject> weakCrosshairGO;
	std::weak_ptr<GameObject> weakCrosshair2GO;
	std::weak_ptr<GameObject> weakColoredGO;

	// Spawner
	weakSpawnerGO = GameObject::createNew();
	auto spawnerGO = weakSpawnerGO.lock();
	if (spawnerGO)
	{
		success &= !(spawnerGO->addComponent<Spawner>().expired());
		success &= !(spawnerGO->addComponent<SceneChanger>().expired());
	}

	// Crosshair1
	weakCrosshairGO = GameObject::createNew();
	auto crosshairGO = weakCrosshairGO.lock();
	if (crosshairGO)
	{
		crosshairGO->transform.setWorldPosition({ 200, 200 });
		crosshairGO->transform.setWorldRotation(45.0);
		crosshairGO->transform.setWorldScale({ 1.5, 1.5 });
		success &= !(crosshairGO->addComponent<Crosshair>().expired());
		success &= !(crosshairGO->addComponent<BehaviourToRemove>().expired());
		//crosshairGO->addBehaviour(new Crosshair2(crosshairGO));
		if (!crosshairGO->addTexture("assets/Crosshair.png"))
		{
			printf("Error: Failed to load crosshair texture image!\n");
			success &= false;
		}
		else
		{
			crosshairGO->texture->setColor(0, 255, 255);
		}
	}
	

	// Crosshair2
	weakCrosshair2GO = GameObject::createNew();
	auto crosshair2GO = weakCrosshair2GO.lock();
	if (crosshair2GO)
	{
		crosshair2GO->transform.setWorldPosition({ constants::SCREEN_WIDTH - 200, 200 });
		success &= !(crosshair2GO->addComponent<Crosshair2>().expired());
		if (!crosshair2GO->addTexture("assets/Crosshair.png"))
		{
			printf("Error: Failed to load crosshair texture image!\n");
			success = false;
		}
		else
		{
			crosshair2GO->texture->setColor(255, 0, 255);
		}
	}
	

	// Colored
	weakColoredGO = GameObject::createNew();
	auto coloredGO = weakColoredGO.lock();
	if (coloredGO)
	{
		if (!coloredGO->addTexture("assets/Crosshair.png"))
		{
			printf("Error: Failed to load crosshair texture image!\n");
			success = false;
		}

		success &= !(coloredGO->addComponent<ColorChanger>().expired());
		coloredGO->transform.setWorldPosition(
		{ 
			(float)(constants::SCREEN_WIDTH - coloredGO->texture->getWidth()) / 2,
			(float)(constants::SCREEN_HEIGHT - coloredGO->texture->getHeight()) 
		});
	}
	
	return success;
}

void TestScene::unload()
{
	// Nothing extra to unload
}
