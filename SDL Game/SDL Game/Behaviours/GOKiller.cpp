#include "GOKiller.h"

#include "Engine/API/API.h"
#include "Engine/GameObjects/GameObject.h"

void GOKiller::update()
{
	if (InputAPI::getKeyDown(SDL_SCANCODE_K))
	{
		GameObject::destroy(gameObject());
	}
}
