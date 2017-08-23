#include "Crosshair.h"

#include "GameObject.h"
#include "Input.h"
#include "Texture.h"


Crosshair::Crosshair(GameObject* parentGameObject) : Behaviour(parentGameObject)
{
	alpha = 255;
}

Crosshair::~Crosshair()
{
}

void Crosshair::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_UP))
	{
		alpha += 16;
		if (alpha > 255)
		{
			alpha = 255;
		}
	}
	if (Input::getKeyDown(SDL_SCANCODE_DOWN))
	{
		alpha -= 16;
		if (alpha < 0)
		{
			alpha = 0;
		}
	}
	
	gameObject->texture->setAlpha(alpha);
}
