#include "TransformPivotScene.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Renderers/Sprite.h"
#include "Engine/Components/Transforms/Transform.h"

#include "Behaviours/Pivotter.h"
#include "Behaviours/SceneChanger.h"
#include "Behaviours/Rotator.h"

bool TransformPivotScene::load()
{
	auto squareGO = GameObject::createNew().lock();
	
	if (auto sprite = squareGO->addComponent<Sprite>().lock())
	{
		sprite->loadImage("assets/Square.png");
	}
	squareGO->addComponent<Pivotter>();
	squareGO->addComponent<SceneChanger>();
	squareGO->transform.lock()->setLocalPosition(Vector2(100, 100));
	
	auto childSquareGO = GameObject::createNew().lock();
	if (auto sprite = childSquareGO->addComponent<Sprite>().lock())
	{
		sprite->loadImage("assets/Square.png");
	}
	childSquareGO->transform.lock()->setParent(squareGO->transform);
	childSquareGO->transform.lock()->setLocalPosition(Vector2(100, 0));
	childSquareGO->addComponent<Rotator>();

	auto child2SquareGO = GameObject::createNew().lock();
	if (auto sprite = child2SquareGO->addComponent<Sprite>().lock())
	{
		sprite->loadImage("assets/Square.png");
	}
	child2SquareGO->transform.lock()->setParent(childSquareGO->transform);
	child2SquareGO->transform.lock()->setLocalPosition(Vector2(100, 0));
	return true;
}

void TransformPivotScene::unload()
{
}
