#include "CollidersScene.h"

#include "Engine/GameObject.h"
#include "Engine/Texture.h"
#include "Engine/Transform.h"
#include "Behaviours/Mover.h"
#include "Behaviours/SceneChanger.h"
#include "Behaviours/TimeLogger.h"
#include "Engine/CircleCollider.h"
#include "Engine/RectangleCollider.h"
#include "Behaviours/Rotator.h"


bool CollidersScene::load()
{
	// Success flag
	bool success = true;
	
	// Bottom left circle with WASDMover
	{
		auto weakGO = GameObject::createNew();
		if (auto go = weakGO.lock())
		{
			go->addComponent<SceneChanger>();
			//go->addComponent<TimeLogger>();

			go->addTexture("assets/Target.png");
			//go->transform.setAllPivots(Vector2(0.5, 0));
			go->transform.setLocalPosition(Vector2(100, 50));
			auto weakColl = go->addComponent<CircleCollider>();
			if (auto coll = weakColl.lock())
			{
				coll->radius = 32;
				//circColl->offset.y = 64;
			}
			auto weakLeftMover = go->addComponent<Mover>();
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
	}

	// Bottom right square with ArrowsMover
	{
		auto weakGO = GameObject::createNew();
		if (auto go = weakGO.lock())
		{
			go->addTexture("assets/Square.png");
			go->addComponent<Rotator>();
			//go->transform.setAllPivots(Vector2(0.5, 0));
			go->transform.setLocalPosition(Vector2(700, 50));
			auto weakColl = go->addComponent<RectangleCollider>();
			if (auto coll = weakColl.lock())
			{
				coll->size = Vector2(100, 100);
				//coll->offset = Vector2(0, 50);
			}
			if ((go->addComponent<Mover>()).lock())
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
	}

	// Mid left circle (non-static)
	{
		auto weakGO = GameObject::createNew();
		if (auto go = weakGO.lock())
		{
			go->addComponent<SceneChanger>();
			go->addTexture("assets/Target.png");
			//go->transform.setAllPivots(Vector2(0.5, 0));
			go->transform.setLocalPosition(Vector2(100, 200));
			auto weakColl = go->addComponent<CircleCollider>();
			if (auto coll = weakColl.lock())
			{
				coll->radius = 32;
				coll->isStatic = false;
			}
		}
		else
		{
			success = false;
		}
	}

	// Mid right square (non-static)
	{
		auto weakGO = GameObject::createNew();
		if (auto go = weakGO.lock())
		{
			go->addComponent<SceneChanger>();
			go->addTexture("assets/Square.png");
			//go->transform.setAllPivots(Vector2(0.5, 0));
			go->transform.setLocalPosition(Vector2(700, 200));
			auto weakColl = go->addComponent<RectangleCollider>();
			if (auto coll = weakColl.lock())
			{
				coll->size = Vector2(100, 100);
				coll->isStatic = false;
			}
		}
		else
		{
			success = false;
		}
	}

	// Top left circle (static)
	{
		auto weakGO = GameObject::createNew();
		if (auto go = weakGO.lock())
		{
			go->addComponent<SceneChanger>();
			go->addTexture("assets/Target.png");
			//go->transform.setAllPivots(Vector2(0.5, 0));
			go->transform.setLocalPosition(Vector2(100, 350));
			auto weakColl = go->addComponent<CircleCollider>();
			if (auto coll = weakColl.lock())
			{
				coll->radius = 32;
				coll->isStatic = true;
			}
		}
		else
		{
			success = false;
		}
	}

	// Mid right square (static)
	{
		auto weakGO = GameObject::createNew();
		if (auto go = weakGO.lock())
		{
			go->addComponent<SceneChanger>();
			go->addTexture("assets/Square.png");
			//go->transform.setAllPivots(Vector2(0.5, 0));
			go->transform.setLocalPosition(Vector2(700, 350));
			auto weakColl = go->addComponent<RectangleCollider>();
			if (auto coll = weakColl.lock())
			{
				coll->size = Vector2(100, 100);
				coll->isStatic = true;
			}
		}
		else
		{
			success = false;
		}
	}

	return success;
}

void CollidersScene::unload()
{
}
