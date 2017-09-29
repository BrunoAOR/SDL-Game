#include "SpriteSheetScene.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Components/Renderers/SpriteSheet.h"
#include "Engine/Components/Renderers/TextRenderer.h"
#include "Engine/Vector2.h"


#include "Behaviours/SpriteSheetController.h"
#include "Behaviours/MegamanController.h"
#include "Behaviours/SceneChanger.h"


bool SpriteSheetScene::load()
{
	// Success flag
	bool success = true;

	{
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
	}

	{
		auto go = GameObject::createNew().lock();
		if (go)
		{
			go->transform.lock()->setLocalPosition(Vector2(400, 300));
			go->addComponent<MegamanController>();
			auto spriteSheet = go->addComponent<SpriteSheet>().lock();
			if (spriteSheet)
			{
				int s = 50;
				spriteSheet->loadImage("assets/MegamanSpritesheet.png");
				spriteSheet->addAnimation("idle");
				spriteSheet->addRectForAnimation("idle", Vector2(0 * s, 0), s, s);
				spriteSheet->addRectForAnimation("idle", Vector2(1 * s, 0), s, s);
				spriteSheet->addRectForAnimation("idle", Vector2(2 * s, 0), s, s);

				spriteSheet->addAnimation("run");
				spriteSheet->addRectForAnimation("run", Vector2(3 * s, 0), s, s);
				spriteSheet->addRectForAnimation("run", Vector2(4 * s, 0), s, s);
				spriteSheet->addRectForAnimation("run", Vector2(5 * s, 0), s, s);
			}
		}
	}

	{
		auto go = GameObject::createNew().lock();
		if (go)
		{
			go->transform.lock()->setLocalPosition(Vector2(400, 500));
			auto textRenderer = go->addComponent<TextRenderer>().lock();
			if (textRenderer)
			{
				textRenderer->setText("It works");
				textRenderer->setColor(255, 0, 0);
			}
		}
	}

	return success;
}


void SpriteSheetScene::unload()
{
}
