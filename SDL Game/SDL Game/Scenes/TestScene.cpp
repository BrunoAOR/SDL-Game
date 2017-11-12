#include "TestScene.h"

#include <memory>

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Renderers/Sprite.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/globals.h"

#include "Behaviours/Crosshair.h"
#include "Behaviours/Crosshair2.h"
#include "Behaviours/Spawner.h"
#include "Behaviours/ColorChanger.h"
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
		crosshairGO->transform.lock()->setWorldPosition({ 200, 200 });
		crosshairGO->transform.lock()->setWorldRotation(45.0);
		crosshairGO->transform.lock()->setWorldScale({ 1.5, 1.5 });
		success &= !(crosshairGO->addComponent<Crosshair>().expired());
		success &= !(crosshairGO->addComponent<BehaviourToRemove>().expired());
		//crosshairGO->addBehaviour(new Crosshair2(crosshairGO));

		if (auto sprite = crosshairGO->addComponent<Sprite>().lock())
		{
			sprite->loadImage("assets/Crosshair.png");
			sprite->setColor(0, 255, 255);
		}
		else
		{
			printf("Error: Failed to load crosshair texture image!\n");
			success &= false;
		}
	}
	

	// Crosshair2
	weakCrosshair2GO = GameObject::createNew();
	auto crosshair2GO = weakCrosshair2GO.lock();
	if (crosshair2GO)
	{
		crosshair2GO->transform.lock()->setWorldPosition({ (double)SCREEN_WIDTH - 200, 200 });
		success &= !(crosshair2GO->addComponent<Crosshair2>().expired());
		
		if (auto sprite = crosshair2GO->addComponent<Sprite>().lock())
		{
			sprite->loadImage("assets/Crosshair.png");
			sprite->setColor(255, 0, 255);
		}
		else
		{
			printf("Error: Failed to load crosshair texture image!\n");
			success &= false;
		}

	}
	

	// Colored
	weakColoredGO = GameObject::createNew();
	auto coloredGO = weakColoredGO.lock();
	if (coloredGO)
	{
		std::shared_ptr<Sprite> sprite = coloredGO->addComponent<Sprite>().lock();
		if (auto sprite = coloredGO->addComponent<Sprite>().lock())
		{
			sprite->loadImage("assets/Crosshair.png");
			coloredGO->transform.lock()->setWorldPosition(
			{
				(float)(SCREEN_WIDTH - sprite->getWidth()) / 2,
				(float)(SCREEN_HEIGHT - sprite->getHeight())
			});
		}
		else
		{
			printf("Error: Failed to load crosshair texture image!\n");
			success = false;
		}

		success &= !(coloredGO->addComponent<ColorChanger>().expired());
		
	}
	
	return success;
}

void TestScene::unload()
{
	// Nothing extra to unload
}
