#include "Pivotter.h"

#include "Engine/Vector2.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Renderers/Sprite.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Input.h"



void Pivotter::start()
{
	positionStep = 10;
	pivotStep = 0.1;
	rotStep = 15;
	position = { 200, 200 };
	rotation = 0;
	scale = { 1, 1 };
	positionPivot = { 0.5, 0.5 };
	rotationPivot = { 0.5, 0.5 };
	scalePivot = { 0.5, 0.5 };

	mode = MoveMode::POS_PIVOT;
	printPivotInfo();
	mode = MoveMode::ROT_PIVOT;
	printPivotInfo();
	mode = MoveMode::SCA_PIVOT;
	printPivotInfo();

	selectedStep = positionStep;
	mode = MoveMode::POSITION;
	updateGO();

	sprite = gameObject()->getComponent<Sprite>();
}

void Pivotter::update()
{
	// Mode change
	if (Input::getKeyDown(SDL_SCANCODE_P))
	{
		selectedStep = positionStep;
		mode = MoveMode::POSITION;
		printf("Entered MoveMode POSITION\n");
	}
	if (Input::getKeyDown(SDL_SCANCODE_O))
	{
		selectedStep = pivotStep;
		mode = MoveMode::POS_PIVOT;
		printf("Entered MoveMode POS_PIVOT\n");
	}
	if (Input::getKeyDown(SDL_SCANCODE_I))
	{
		selectedStep = pivotStep;
		mode = MoveMode::ROT_PIVOT;
		printf("Entered MoveMode ROT_PIVOT\n");
	}
	if (Input::getKeyDown(SDL_SCANCODE_U))
	{
		selectedStep = pivotStep;
		mode = MoveMode::SCA_PIVOT;
		printf("Entered MoveMode SCA_PIVOT\n");
	}

	// Pivot moving
	if (Input::getKeyDown(SDL_SCANCODE_UP))
	{
		movePivot(getActivePivot(), Direction::UP);
		printPivotInfo();
	}
	if (Input::getKeyDown(SDL_SCANCODE_DOWN))
	{
		movePivot(getActivePivot(), Direction::DOWN);
		printPivotInfo();
	}
	if (Input::getKeyDown(SDL_SCANCODE_LEFT))
	{
		movePivot(getActivePivot(), Direction::LEFT);
		printPivotInfo();
	}
	if (Input::getKeyDown(SDL_SCANCODE_RIGHT))
	{
		movePivot(getActivePivot(), Direction::RIGHT);
		printPivotInfo();
	}

	// Rotation
	if (Input::getKeyDown(SDL_SCANCODE_Q))
	{
		rotation += rotStep;
		printf("Rotation: %2.0f\n", rotation);
	}
	if (Input::getKeyDown(SDL_SCANCODE_E))
	{
		rotation -= rotStep;
		printf("Rotation: %2.0f\n", rotation);
	}

	// Scaling
	if (Input::getKeyDown(SDL_SCANCODE_W))
	{
		scale.y += pivotStep;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}
	if (Input::getKeyDown(SDL_SCANCODE_S))
	{
		scale.y -= pivotStep;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}
	if (Input::getKeyDown(SDL_SCANCODE_D))
	{
		scale.x += pivotStep;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}
	if (Input::getKeyDown(SDL_SCANCODE_A))
	{
		scale.x -= pivotStep;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}

	updateGO();
}

void Pivotter::updateGO()
{
	auto go = gameObject();
	auto transform = go->transform.lock();
	transform->setLocalPosition(position);
	transform->setLocalRotation(rotation);
	transform->setLocalScale(scale);
	if (auto lockedSprite = sprite.lock())
	{
		lockedSprite->setPositionPivot(positionPivot);
		lockedSprite->setRotationPivot(rotationPivot);
		lockedSprite->setScalePivot(scalePivot);
	}
}

void Pivotter::printPivotInfo()
{
	Vector2& pivot = getActivePivot();
	switch (mode)
	{
	case Pivotter::MoveMode::POSITION:
		printf("Position at ( %1.1f , %1.1f )\n", pivot.x, pivot.y);
		break;
	case Pivotter::MoveMode::POS_PIVOT:
		printf("POS Pivot at ( %1.1f , %1.1f )\n", pivot.x, pivot.y);
		break;
	case Pivotter::MoveMode::ROT_PIVOT:
		printf("ROT Pivot at ( %1.1f , %1.1f )\n", pivot.x, pivot.y);
		break;
	case Pivotter::MoveMode::SCA_PIVOT:
		printf("SCA Pivot at ( %1.1f , %1.1f )\n", pivot.x, pivot.y);
		break;
	default:
		printf("Fail!");
		break;
	}

}

Vector2 & Pivotter::getActivePivot()
{
	switch (mode)
	{
	case Pivotter::MoveMode::POSITION:
		return position;
	case Pivotter::MoveMode::POS_PIVOT:
		return positionPivot;
	case Pivotter::MoveMode::ROT_PIVOT:
		return rotationPivot;
	case Pivotter::MoveMode::SCA_PIVOT:
		return scalePivot;
	default:
		return positionPivot;
	}
}

void Pivotter::movePivot(Vector2& pivot, const Direction & direction)
{
	switch (direction)
	{
	case Direction::UP:
		pivot.y += selectedStep;
		break;
	case Direction::DOWN:
		pivot.y -= selectedStep;
		break;
	case Direction::LEFT:
		pivot.x -= selectedStep;
		break;
	case Direction::RIGHT:
		pivot.x += selectedStep;
		break;
	}
}
