#include "TimeTesterScene.h"

#include "Engine/GameObject.h"
#include "Engine/Texture.h"
#include "Engine/Transform.h"
#include "Behaviours/Mover.h"
#include "Behaviours/SceneChanger.h"

bool TimeTesterScene::load()
{
	// Success flag
	bool success = true;

	auto weakLeftGO = GameObject::createNew();
	if (auto leftGO = weakLeftGO.lock())
	{
		leftGO->addComponent<SceneChanger>();
		leftGO->addTexture("assets/Square.png");
		leftGO->texture->setAllPivots(Vector2(0.5, 0));
		leftGO->transform.lock()->setLocalPosition(Vector2(100, 200));
		auto weakLeftMover = leftGO->addComponent<Mover>();
		if (auto leftMover = weakLeftMover.lock())
		{
			leftMover->useWASD = true;
		}
		else
		{
			success = false;
		}
	}
	else
	{
		success = false;
	}

	auto weakRightGO = GameObject::createNew();
	if (auto rightGO = weakRightGO.lock())
	{
		rightGO->addTexture("assets/Square.png");
		rightGO->texture->setAllPivots(Vector2(0.5, 0));
		rightGO->transform.lock()->setLocalPosition(Vector2(700, 200));
		if ((rightGO->addComponent<Mover>()).lock())
		{
			success &= true;
		}
		else
		{
			success = false;
		}
	}
	else
	{
		success = false;
	}

	return success;
}


void TimeTesterScene::unload()
{
}
