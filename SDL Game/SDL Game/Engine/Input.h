#pragma once

#include <map>
#include <SDL.h>


class Input
{
public:
	~Input();
	static bool getKey(SDL_Scancode scancode);
	static bool getKeyUp(SDL_Scancode scancode);
	static bool getKeyDown(SDL_Scancode scancode);

	static void clearStates();
	static void setKeyUp(SDL_Scancode scancode);
	static void setKeyDown(SDL_Scancode scancode);

private:
	Input();

	enum class KeyState {
		UP,
		DOWN
	};
	
	static const Uint8* currentKeyStates;
	static std::map<SDL_Scancode, KeyState> keyUpDownStates;
};

