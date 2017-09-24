#include "ParentSwitchScene.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Behaviours/SceneChanger.h"
#include "Behaviours/Rotator.h"
#include "Behaviours/Mover.h"
#include "Behaviours/ParentSwitcher.h"
#include "Behaviours/TimeLogger.h"

bool ParentSwitchScene::load()
{
	// Success flag
	bool success = true;

	// Bottom left circle with WASDMover
	auto leftGO = GameObject::createNew().lock();	
	if (leftGO)
	{
		leftGO->addComponent<SceneChanger>();
		leftGO->addComponent<TimeLogger>();

		leftGO->addTexture("assets/Target.png");
		//go->transform.setAllPivots(Vector2(0.5, 0));
		leftGO->transform.lock()->setLocalPosition(Vector2(100, 50));
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

	// Bottom right square with ArrowsMover
	auto rightGO = GameObject::createNew().lock();
	if (rightGO)
	{
		rightGO->addTexture("assets/Square.png");
		rightGO->addComponent<Rotator>();
		//go->transform.setAllPivots(Vector2(0.5, 0));
		rightGO->transform.lock()->setLocalPosition(Vector2(700, 50));
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
	
	// Parent switcher
	auto switchGO = GameObject::createNew().lock();
	{
		if (switchGO)
		{
			switchGO->addTexture("assets/Square.png");
			switchGO->transform.lock()->setLocalPosition(Vector2(400, 200));
			auto parentSwitcher = switchGO->addComponent<ParentSwitcher>().lock();
			if (parentSwitcher)
			{
				parentSwitcher->parent1 = leftGO->transform;
				parentSwitcher->parent2 = rightGO->transform;
			}
		}
	}

	return success;
}

void ParentSwitchScene::unload()
{
}
