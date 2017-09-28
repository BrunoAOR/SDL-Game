#include "GOKiller.h"

#include "Engine/Input.h"
#include "Engine/GameObjects/GameObject.h"

void GOKiller::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_K))
	{
		GameObject::destroy(gameObject());
	}
}
