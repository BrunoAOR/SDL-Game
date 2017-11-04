#include "Rotator.h"

#include "Engine/API/API.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"


void Rotator::update()
{
	double rotation = gameObject()->transform.lock()->getLocalRotation();
	double rotStep = 15;
	if (InputAPI::getKeyDown(SDL_SCANCODE_R))
	{
		rotation += rotStep;
		printf("Rotation: %2.0f\n", rotation);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_Y))
	{
		rotation -= rotStep;
		printf("Rotation: %2.0f\n", rotation);
	}
	gameObject()->transform.lock()->setLocalRotation(rotation);
}
