#include "SceneChanger.h"

#include "Engine/Input.h"
#include "Engine/SceneManager.h"

void SceneChanger::awake()
{
}

void SceneChanger::start()
{
}

void SceneChanger::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_1))
	{
		SceneManager::loadScene(0);
	}
	if (Input::getKeyDown(SDL_SCANCODE_2))
	{
		SceneManager::loadScene(1);
	}
}
