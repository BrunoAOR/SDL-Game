#include "TestScene.h"

#include "Engine/GameObject.h"
#include "Engine/constants.h"
#include "Engine/Texture.h"
#include "Crosshair.h"
#include "Crosshair2.h"
#include "Spawner.h"
#include "ColorChanger.h"


TestScene::TestScene()
{
	m_crosshairGO = nullptr;
	m_crosshair2GO = nullptr;
	m_spawnerGO = nullptr;
	m_coloredGO = nullptr;
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

	// Spawner
	m_spawnerGO = new GameObject();
	m_spawnerGO->addBehaviour<Spawner>();

	// Crosshair1
	m_crosshairGO = new GameObject();
	m_crosshairGO->transform.position = { 200, 200 };
	success &= m_crosshairGO->addBehaviour<Crosshair>();
	success &= m_crosshairGO->addBehaviour<Crosshair2>();
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
	m_crosshair2GO = new GameObject();
	m_crosshair2GO->transform.position = { constants::SCREEN_WIDTH - 200, 200 };
	success &= m_crosshair2GO->addBehaviour<Crosshair2>();
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
	m_coloredGO = new GameObject();
	if (!m_coloredGO->addTexture("assets/Crosshair.png"))
	{
		printf("Error: Failed to load crosshair texture image!\n");
		success = false;
	}
	
	success &= m_coloredGO->addBehaviour<ColorChanger>();
	m_coloredGO->transform.position = { (float)(constants::SCREEN_WIDTH - m_coloredGO->texture->getWidth()) / 2, (float)(constants::SCREEN_HEIGHT - m_coloredGO->texture->getHeight())};
	return success;
}

void TestScene::unload()
{
	// Free loaded GameObjects
	delete m_crosshairGO;
	m_crosshairGO = nullptr;
	delete m_crosshair2GO;
	m_crosshair2GO = nullptr;
	delete m_spawnerGO;
	m_spawnerGO = nullptr;
	delete m_coloredGO;
	m_coloredGO = nullptr;
}
