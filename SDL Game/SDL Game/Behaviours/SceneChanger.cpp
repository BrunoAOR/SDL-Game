#include "SceneChanger.h"

#include "Engine/API/API.h"


void SceneChanger::update()
{
	if (InputAPI::getKeyDown(SDL_SCANCODE_1))
	{
		ScenesAPI::loadScene(0);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_2))
	{
		ScenesAPI::loadScene(1);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_3))
	{
		ScenesAPI::loadScene(2);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_4))
	{
		ScenesAPI::loadScene(3);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_5))
	{
		ScenesAPI::loadScene(4);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_6))
	{
		ScenesAPI::loadScene(5);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_7))
	{
		ScenesAPI::loadScene(6);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_8))
	{
		ScenesAPI::loadScene(7);
	}
}
