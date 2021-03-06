#include "ColorChanger.h"

#include "Engine/API/API.h"
#include "Engine/Components/Renderers/Sprite.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"


#include "Behaviours/Crosshair2.h"


void ColorChanger::start()
{
	color1[0] = 0;
	color1[1] = 255;
	color1[2] = 255;

	color2[0] = 255;
	color2[0] = 0;
	color2[0] = 255;

	color1active = true;
	hasCrosshair = false;
	
	sprite = gameObject()->getComponent<Sprite>();
	if (auto lockedSprite = sprite.lock())
	{
		lockedSprite->setColor(color1[0], color1[1], color1[2]);
	}
}


void ColorChanger::update()
{
	if (InputAPI::getKeyDown(SDL_SCANCODE_C))
	{
		if (color1active)
		{
			color1active = false;
			if (auto lockedSprite = sprite.lock())
			{
				lockedSprite->setColor(color2[0], color2[1], color2[2]);
			}
		}
		else
		{
			color1active = true;
			if (auto lockedSprite = sprite.lock())
			{
				lockedSprite->setColor(color1[0], color1[1], color1[2]);
			}
		}
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_V))
	{
		if (hasCrosshair)
		{
			gameObject()->removeComponent(gameObject()->getComponent<Crosshair2>());
			hasCrosshair = false;
		}
		else
		{
			gameObject()->addComponent<Crosshair2>();
			hasCrosshair = true;
		}
	}
}
