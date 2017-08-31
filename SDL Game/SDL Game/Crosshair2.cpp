#include "Crosshair2.h"

#include "Engine/GameObject.h"
#include "Engine/Input.h"


void Crosshair2::start()
{
	angle = 0;
}


void Crosshair2::update()
{
	angle += 0.1;
	if (angle >= 360) {
		angle -= 360;
	}
	gameObject()->transform.rotation = angle;
	
	if (Input::getKeyDown(SDL_SCANCODE_UP))
	{
		gameObject()->transform.position.y -= stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_DOWN))
	{
		gameObject()->transform.position.y += stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_LEFT))
	{
		gameObject()->transform.position.x -= stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_RIGHT))
	{
		gameObject()->transform.position.x += stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_0))
	{
		if (gameObject()->isActive())
		{
			gameObject()->setActive(false);
		}
		else
		{
			gameObject()->setActive(true);
		}
	}
}
