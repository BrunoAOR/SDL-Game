#pragma once

#include <map>
#include <SDL_stdinc.h>
#include <SDL_scancode.h>


class Input
{
public:
	Input();
	~Input();

	bool getKey(SDL_Scancode scancode);
	bool getKeyUp(SDL_Scancode scancode);
	bool getKeyDown(SDL_Scancode scancode);

	void clearStates();
	void setKeyUp(SDL_Scancode scancode);
	void setKeyDown(SDL_Scancode scancode);

private:
	enum class KeyState {
		UP,
		DOWN
	};
	
	const Uint8* currentKeyStates;
	std::map<SDL_Scancode, KeyState> keyUpDownStates;
};
