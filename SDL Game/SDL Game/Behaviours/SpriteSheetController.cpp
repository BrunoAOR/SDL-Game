#include "SpriteSheetController.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Input.h"


void SpriteSheetController::start()
{
	spriteSheet = gameObject()->getComponent<SpriteSheet>();
}


void SpriteSheetController::update()
{
	auto sheet = spriteSheet.lock();
	if (!sheet) {
		return;
	}

	if (Input::getKeyDown(SDL_SCANCODE_UP))
	{
		sheet->selectAnimation("high");
	}
	if (Input::getKeyDown(SDL_SCANCODE_DOWN))
	{
		sheet->selectAnimation("low");
	}
	if (Input::getKeyDown(SDL_SCANCODE_LEFT))
	{
		sheet->previousAnimationFrame();
	}
	if (Input::getKeyDown(SDL_SCANCODE_RIGHT))
	{
		sheet->nextAnimationFrame();
	}

	if (Input::getKeyDown(SDL_SCANCODE_S))
	{
		sheet->stopAnimation();
	}
	if (Input::getKeyDown(SDL_SCANCODE_Q))
	{
		sheet->playAnimation("high", -4);
	}
	if (Input::getKeyDown(SDL_SCANCODE_E))
	{
		sheet->playAnimation("high", 4);
	}
	if (Input::getKeyDown(SDL_SCANCODE_Z))
	{
		sheet->playAnimation("low", -4);
	}
	if (Input::getKeyDown(SDL_SCANCODE_C))
	{
		sheet->playAnimation("low", 4);

	}
	



}
