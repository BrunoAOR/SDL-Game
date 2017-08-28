#include "TestScene.h"

#include "Engine/GameObject.h"
#include "Engine/constants.h"
#include "Engine/Texture.h"
#include "Crosshair.h"
#include "Crosshair2.h"
#include "Spawner.h"
#include "ColorChanger.h"
#include "BehaviourToRemove.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	unload();
}

bool TestScene::load()
{
	// Loading success flag
	bool success = true;

	// Load gameobjects
	GameObject* m_spawnerGO;
	GameObject* m_crosshairGO;
	GameObject* m_crosshair2GO;
	GameObject* m_coloredGO;

	// Spawner
	m_spawnerGO = GameObject::createNew();
	m_spawnerGO->addComponent<Spawner>();

	// Crosshair1
	m_crosshairGO = GameObject::createNew();
	m_crosshairGO->transform.position = { 200, 200 };
	success &= m_crosshairGO->addComponent<Crosshair>();
	success &= m_crosshairGO->addComponent<Crosshair2>();
	success &= m_crosshairGO->addComponent<BehaviourToRemove>();
	//crosshairGO->addBehaviour(new Crosshair2(crosshairGO));
	if (!m_crosshairGO->addTexture("assets/Crosshair.png"))
	{
		printf("Error: Failed to load crosshair texture image!\n");
		success = false;
	}
	else
	{
		m_crosshairGO->texture->setColor(0, 255, 255);
	}

	// Crosshair2
	m_crosshair2GO = GameObject::createNew();
	m_crosshair2GO->transform.position = { constants::SCREEN_WIDTH - 200, 200 };
	success &= m_crosshair2GO->addComponent<Crosshair2>();
	if (!m_crosshair2GO->addTexture("assets/Crosshair.png"))
	{
		printf("Error: Failed to load crosshair texture image!\n");
		success = false;
	}
	else
	{
		m_crosshair2GO->texture->setColor(255, 0, 255);
	}

	// Colored
	m_coloredGO = GameObject::createNew();
	if (!m_coloredGO->addTexture("assets/Crosshair.png"))
	{
		printf("Error: Failed to load crosshair texture image!\n");
		success = false;
	}
	
	success &= m_coloredGO->addComponent<ColorChanger>();
	m_coloredGO->transform.position = { (float)(constants::SCREEN_WIDTH - m_coloredGO->texture->getWidth()) / 2, (float)(constants::SCREEN_HEIGHT - m_coloredGO->texture->getHeight())};
	return success;
}

void TestScene::unload()
{
	// Nothing extra to unload
}
