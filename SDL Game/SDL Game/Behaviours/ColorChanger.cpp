#include "ColorChanger.h"

#include "Engine/Input.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Texture.h"

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
	
	gameObject()->texture->setColor(color1[0], color1[1], color1[2]);
}


void ColorChanger::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_C))
	{
		if (color1active)
		{
			color1active = false;
			gameObject()->texture->setColor(color2[0], color2[1], color2[2]);
		}
		else
		{
			color1active = true;
			gameObject()->texture->setColor(color1[0], color1[1], color1[2]);
		}
	}
	if (Input::getKeyDown(SDL_SCANCODE_V))
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
