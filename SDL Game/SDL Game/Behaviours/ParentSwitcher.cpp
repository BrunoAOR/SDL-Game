#include "ParentSwitcher.h"

#include "Engine/API/API.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"

void ParentSwitcher::update()
{
	if (InputAPI::getKeyDown(SDL_SCANCODE_Z))
	{
		gameObject()->transform.lock()->setParent(parent1);
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_X))
	{
		gameObject()->transform.lock()->setParent(parent2);
	}
}
