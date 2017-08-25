#include "ColorChanger.h"

#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "Engine/Texture.h"

ColorChanger::ColorChanger(GameObject* parentGameObject): Behaviour(parentGameObject)
{
	color1[0] = 0;
	color1[1] = 255;
	color1[2] = 255;

	color2[0] = 255;
	color2[0] = 0;
	color2[0] = 255;

	color1active = true;

	gameObject->texture->setColor(color1[0], color1[1], color1[2]);
}


ColorChanger::~ColorChanger()
{
}

void ColorChanger::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_C)) {
		if (color1active) {
			color1active = false;
			gameObject->texture->setColor(color2[0], color2[1], color2[2]);
		}
		else {
			color1active = true;
			gameObject->texture->setColor(color1[0], color1[1], color1[2]);
		}
	}
}
