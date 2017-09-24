#include "TransformPivotScene.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Behaviours/Pivotter.h"
#include "Behaviours/SceneChanger.h"
#include "Behaviours/Rotator.h"

bool TransformPivotScene::load()
{
	auto squareGO = GameObject::createNew().lock();
	
	squareGO->addTexture("assets/Square.png");
	squareGO->addComponent<Pivotter>();
	squareGO->addComponent<SceneChanger>();
	squareGO->transform.lock()->setLocalPosition(Vector2(100, 100));
	
	auto childSquareGO = GameObject::createNew().lock();
	childSquareGO->addTexture("assets/Square.png");
	childSquareGO->transform.lock()->setParent(squareGO->transform);
	childSquareGO->transform.lock()->setLocalPosition(Vector2(100, 0));
	childSquareGO->addComponent<Rotator>();

	auto child2SquareGO = GameObject::createNew().lock();
	child2SquareGO->addTexture("assets/Square.png");
	child2SquareGO->transform.lock()->setParent(childSquareGO->transform);
	child2SquareGO->transform.lock()->setLocalPosition(Vector2(100, 0));
	return true;
}

void TransformPivotScene::unload()
{
}
