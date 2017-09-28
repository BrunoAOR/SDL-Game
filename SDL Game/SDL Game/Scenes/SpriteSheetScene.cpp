#include "SpriteSheetScene.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Components/Renderers/SpriteSheet.h"
#include "Engine/Vector2.h"

#include "Behaviours/SpriteSheetController.h"
#include "Behaviours/SceneChanger.h"


bool SpriteSheetScene::load()
{
	// Success flag
	bool success = true;

	auto go = GameObject::createNew().lock();
	if (go)
	{
		go->transform.lock()->setLocalPosition(Vector2(300, 300));
		go->addComponent<SceneChanger>();
		go->addComponent<SpriteSheetController>();
		auto spriteSheet = go->addComponent<SpriteSheet>().lock();
		if (spriteSheet)
		{
			spriteSheet->loadImage("assets/Spritesheet.png");
			spriteSheet->addAnimation("low");
			spriteSheet->addRectForAnimation("low", Vector2(0, 0), 32, 32);
			spriteSheet->addRectForAnimation("low", Vector2(32, 0), 32, 32);
			spriteSheet->addRectForAnimation("low", Vector2(64, 0), 32, 32);
			spriteSheet->addRectForAnimation("low", Vector2(96, 0), 32, 32);
			spriteSheet->addRectForAnimation("low", Vector2(0, 32), 32, 32);
			spriteSheet->addRectForAnimation("low", Vector2(32, 32), 32, 32);
			spriteSheet->addRectForAnimation("low", Vector2(64, 32), 32, 32);
			spriteSheet->addRectForAnimation("low", Vector2(96, 32), 32, 32);
			spriteSheet->addAnimation("high");
			spriteSheet->addRectForAnimation("high", Vector2(0, 64), 32, 32);
			spriteSheet->addRectForAnimation("high", Vector2(32, 64), 32, 32);
			spriteSheet->addRectForAnimation("high", Vector2(64, 64), 32, 32);
			spriteSheet->addRectForAnimation("high", Vector2(96, 64), 32, 32);
			spriteSheet->addRectForAnimation("high", Vector2(0, 96), 32, 32);
			spriteSheet->addRectForAnimation("high", Vector2(32, 96), 32, 32);
			spriteSheet->addRectForAnimation("high", Vector2(64, 96), 32, 32);
			spriteSheet->addRectForAnimation("high", Vector2(96, 96), 32, 32);
		}
	}

	return success;
}


void SpriteSheetScene::unload()
{
}
