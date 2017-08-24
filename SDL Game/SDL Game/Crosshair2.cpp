#include "Crosshair2.h"

#include "Engine/GameObject.h"
#include "Engine/Input.h"

Crosshair2::Crosshair2(GameObject* parentGameObject) : Behaviour(parentGameObject)
{

}


Crosshair2::~Crosshair2()
{
}

void Crosshair2::update()
{
	
	if (Input::getKeyDown(SDL_SCANCODE_UP))
	{
		gameObject->transform.position.y -= stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_DOWN))
	{
		gameObject->transform.position.y += stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_LEFT))
	{
		gameObject->transform.position.x -= stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_RIGHT))
	{
		gameObject->transform.position.x += stepSize;
	}
}
