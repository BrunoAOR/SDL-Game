#include "Crosshair2.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Input.h"


void Crosshair2::start()
{
	angle = 0;
}


void Crosshair2::update()
{
	// Rotation
	angle += 0.1;
	if (angle >= 360) {
		angle -= 360;
	}
	gameObject()->transform.lock()->setWorldRotation(angle);
	
	// Position
	Vector2 currentPos = gameObject()->transform.lock()->getLocalPosition();
	if (Input::getKeyDown(SDL_SCANCODE_UP))
	{
		currentPos.y += stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_DOWN))
	{
		currentPos.y -= stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_LEFT))
	{
		currentPos.x -= stepSize;
	}
	if (Input::getKeyDown(SDL_SCANCODE_RIGHT))
	{
		currentPos.x += stepSize;
	}
	gameObject()->transform.lock()->setLocalPosition(currentPos);

	// On/off
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
