#include "MegamanController.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Renderers/SpriteSheet.h"
#include "Engine/Input.h"

void MegamanController::start()
{
	animationSpeed = 5;
	spriteSheet = gameObject()->getComponent<SpriteSheet>();
	if (auto sprite = spriteSheet.lock())
	{
		sprite->selectAnimation("idle");
	}
}

void MegamanController::update()
{
	auto sprite = spriteSheet.lock();

	if (!sprite)
	{
		return;
	}

	if (Input::getKeyDown(SDL_SCANCODE_KP_0))
	{
		sprite->stopAnimation();
	}
	if (Input::getKeyDown(SDL_SCANCODE_KP_1))
	{
		sprite->playAnimation("idle", animationSpeed);
	}
	if (Input::getKeyDown(SDL_SCANCODE_KP_2))
	{
		sprite->playAnimation("run", animationSpeed);
	}

	if (Input::getKeyDown(SDL_SCANCODE_KP_PLUS))
	{
		sprite->setAnimationSpeed(++animationSpeed);
		printf("Anim speed: %i\n", animationSpeed);
	}
	if (Input::getKeyDown(SDL_SCANCODE_KP_MINUS))
	{
		sprite->setAnimationSpeed(--animationSpeed);
		printf("Anim speed: %i\n", animationSpeed);
	}
}
