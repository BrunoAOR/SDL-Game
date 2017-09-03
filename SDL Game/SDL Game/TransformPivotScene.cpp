#include "TransformPivotScene.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Pivotter.h"
#include "SceneChanger.h"

bool TransformPivotScene::load()
{
	auto squareGO = GameObject::createNew();
	squareGO.lock()->addTexture("assets/Square.png");
	squareGO.lock()->addComponent<Pivotter>();
	squareGO.lock()->addComponent<SceneChanger>();
	return true;
}

void TransformPivotScene::unload()
{
}
