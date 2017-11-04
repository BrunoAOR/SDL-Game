#pragma once

#include <SDL_scancode.h>

namespace ScenesAPI
{
	void loadScene(unsigned int index);
}

namespace InputAPI
{
	bool getKey(SDL_Scancode scancode);
	bool getKeyUp(SDL_Scancode scancode);
	bool getKeyDown(SDL_Scancode scancode);
}


namespace TimeAPI
{
	Uint32 time();
	Uint32 deltaTime();
}
