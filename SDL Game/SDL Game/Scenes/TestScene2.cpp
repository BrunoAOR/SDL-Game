#include "TestScene2.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"

#include "Behaviours/Crosshair2.h"
#include "Behaviours/ColorChanger.h"
#include "Behaviours/SceneChanger.h"

bool TestScene2::load()
{
	// Success flag
	bool success = true;

	auto go = GameObject::createNew().lock();

	if (go) {
		go->transform.lock()->setWorldPosition({ 300, 300 });
		success &= !(go->addComponent<Crosshair2>().expired());
		success &= !(go->addComponent<ColorChanger>().expired());
		success &= !(go->addComponent<SceneChanger>().expired());
		success &= go->addTexture("assets/Target.png");
	}

	return success;
}

void TestScene2::unload()
{
}
