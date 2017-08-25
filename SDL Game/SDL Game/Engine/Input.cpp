#include "Input.h"


const Uint8* Input::currentKeyStates = SDL_GetKeyboardState(NULL);
std::map<SDL_Scancode, Input::KeyState> Input::keyUpDownStates;


Input::Input()
{
}


bool Input::getKey(SDL_Scancode scancode)
{
	return currentKeyStates[scancode];
}


bool Input::getKeyUp(SDL_Scancode scancode)
{
	if (keyUpDownStates.count(scancode))
	{
		return keyUpDownStates[scancode] == KeyState::UP;
	}
	return false;
}


bool Input::getKeyDown(SDL_Scancode scancode)
{
	if (keyUpDownStates.count(scancode))
	{
		return keyUpDownStates[scancode] == KeyState::DOWN;
	}
	return false;
}


void Input::clearStates()
{
	keyUpDownStates.clear();
}


void Input::setKeyUp(SDL_Scancode scancode)
{
	keyUpDownStates[scancode] = KeyState::UP;
}


void Input::setKeyDown(SDL_Scancode scancode)
{
	keyUpDownStates[scancode] = KeyState::DOWN;
}
