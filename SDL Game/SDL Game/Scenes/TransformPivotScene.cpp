#include "TransformPivotScene.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Behaviours/Pivotter.h"
#include "Behaviours/SceneChanger.h"
#include "Behaviours/Rotator.h"

bool TransformPivotScene::load()
{
	auto squareGO = GameObject::createNew();
	squareGO.lock()->addTexture("assets/Square.png");
	squareGO.lock()->addComponent<Pivotter>();
	squareGO.lock()->addComponent<SceneChanger>();
	
	auto childSquareGO = GameObject::createNew();
	childSquareGO.lock()->addTexture("assets/Square.png");
	childSquareGO.lock()->setParent(squareGO);
	childSquareGO.lock()->transform.setLocalPosition(Vector2(100, 0));
	childSquareGO.lock()->addComponent<Rotator>();

	auto child2SquareGO = GameObject::createNew();
	child2SquareGO.lock()->addTexture("assets/Square.png");
	child2SquareGO.lock()->setParent(childSquareGO);
	child2SquareGO.lock()->transform.setLocalPosition(Vector2(100, 0));
	return true;
}

void TransformPivotScene::unload()
{
}
