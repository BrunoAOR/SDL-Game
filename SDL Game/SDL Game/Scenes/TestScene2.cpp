#include "TestScene2.h"

#include "Engine/GameObject.h"
#include "Behaviours/Crosshair2.h"
#include "Behaviours/ColorChanger.h"
#include "Behaviours/SceneChanger.h"

bool TestScene2::load()
{
	// Success flag
	bool success = true;

	auto go = GameObject::createNew().lock();

	if (go) {
		go->transform.setWorldPosition({ 300, 300 });
		success &= go->addComponent<Crosshair2>();
		success &= go->addComponent<ColorChanger>();
		success &= go->addComponent<SceneChanger>();
		success &= go->addTexture("assets/Target.png");
	}

	return success;
}

void TestScene2::unload()
{
}