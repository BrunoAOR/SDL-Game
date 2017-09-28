#include "SceneChanger.h"

#include "Engine/Input.h"
#include "Engine/Scenes/SceneManager.h"


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
	if (Input::getKeyDown(SDL_SCANCODE_3))
	{
		SceneManager::loadScene(2);
	}
	if (Input::getKeyDown(SDL_SCANCODE_4))
	{
		SceneManager::loadScene(3);
	}
	if (Input::getKeyDown(SDL_SCANCODE_5))
	{
		SceneManager::loadScene(4);
	}
	if (Input::getKeyDown(SDL_SCANCODE_6))
	{
		SceneManager::loadScene(5);
	}
	if (Input::getKeyDown(SDL_SCANCODE_7))
	{
		SceneManager::loadScene(6);
	}
	if (Input::getKeyDown(SDL_SCANCODE_8))
	{
		SceneManager::loadScene(7);
	}
}
