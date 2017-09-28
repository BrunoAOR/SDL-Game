#include "ParentSwitcher.h"

#include "Engine/Input.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"

void ParentSwitcher::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_Z))
	{
		gameObject()->transform.lock()->setParent(parent1);
	}
	if (Input::getKeyDown(SDL_SCANCODE_X))
	{
		gameObject()->transform.lock()->setParent(parent2);
	}
}
