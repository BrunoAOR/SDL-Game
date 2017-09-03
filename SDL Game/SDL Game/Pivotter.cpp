#include "Pivotter.h"

#include "Engine/Vector2.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Input.h"



void Pivotter::start()
{
	step = 0.1;
	rotStep = 15;
	position = { 200, 200 };
	rotation = 0;
	scale = { 1, 1 };
	positionPivot = { 0, 0 };
	rotationPivot = { 0, 0 };
	scalePivot = { 0, 0 };

	mode = MoveMode::POS;
	printPivotInfo();
	mode = MoveMode::ROT;
	printPivotInfo();
	mode = MoveMode::SCA;
	printPivotInfo();
	mode = MoveMode::POS;
}

void Pivotter::update()
{
	// Mode change
	if (Input::getKeyDown(SDL_SCANCODE_P))
	{
		mode = MoveMode::POS;
		printf("Entered MoveMode POS\n");
	}
	if (Input::getKeyDown(SDL_SCANCODE_O))
	{
		mode = MoveMode::ROT;
		printf("Entered MoveMode ROT\n");
	}
	if (Input::getKeyDown(SDL_SCANCODE_I))
	{
		mode = MoveMode::SCA;
		printf("Entered MoveMode SCA\n");
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
		rotation -= rotStep;
		printf("Rotation: %2.0f\n", rotation);
	}
	if (Input::getKeyDown(SDL_SCANCODE_E))
	{
		rotation += rotStep;
		printf("Rotation: %2.0f\n", rotation);
	}

	// Scaling
	if (Input::getKeyDown(SDL_SCANCODE_W))
	{
		scale.y += step;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}
	if (Input::getKeyDown(SDL_SCANCODE_S))
	{
		scale.y -= step;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}
	if (Input::getKeyDown(SDL_SCANCODE_D))
	{
		scale.x += step;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}
	if (Input::getKeyDown(SDL_SCANCODE_A))
	{
		scale.x -= step;
		printf("Scale: ( %2.1f , %2.1f )\n", scale.x, scale.y);
	}

	updateGO();
}

void Pivotter::updateGO()
{
	auto go = gameObject();

	go->transform.setWorldPosition(position);
	go->transform.setWorldRotation(rotation);
	go->transform.setWorldScale(scale);
	go->transform.setPositionPivot(positionPivot);
	go->transform.setRotationPivot(rotationPivot);
	go->transform.setScalePivot(scalePivot);
}

void Pivotter::printPivotInfo()
{
	Vector2& pivot = getActivePivot();
	switch (mode)
	{
	case Pivotter::MoveMode::POS:
		printf("POS Pivot at ( %1.1f , %1.1f )\n", pivot.x, pivot.y);
		break;
	case Pivotter::MoveMode::ROT:
		printf("ROT Pivot at ( %1.1f , %1.1f )\n", pivot.x, pivot.y);
		break;
	case Pivotter::MoveMode::SCA:
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
	case Pivotter::MoveMode::POS:
		return positionPivot;
	case Pivotter::MoveMode::ROT:
		return rotationPivot;
	case Pivotter::MoveMode::SCA:
		return scalePivot;
	default:
		return positionPivot;
	}
}

void Pivotter::movePivot(Vector2 & pivot, const Direction & direction)
{
	switch (direction)
	{
	case Direction::UP:
		pivot.y += step;
		/*if (pivot.y < 0) {
			pivot.y = 0;
		}*/
		break;
	case Direction::DOWN:
		pivot.y -= step;
		/*if (pivot.y > 1) {
			pivot.y = 1;
		}*/
		break;
	case Direction::LEFT:
		pivot.x -= step;
		/*if (pivot.x < 0) {
			pivot.x = 0;
		}*/
		break;
	case Direction::RIGHT:
		pivot.x += step;
		/*if (pivot.x > 1) {
			pivot.x = 1;
		}*/
		break;
	}
}
