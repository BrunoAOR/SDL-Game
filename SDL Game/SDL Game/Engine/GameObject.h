#pragma once

#include <string>
#include <SDL.h>

#include "Transform.h"

class Texture;
class Behaviour;


class GameObject
{
public:
	Transform transform;
	Texture* texture;
	Behaviour* behaviour;
	
	GameObject(SDL_Renderer* renderer);
	~GameObject();

	bool addTexture(std::string path);
	void removeTexture();

private:
	// The renderer associated with this texture
	SDL_Renderer* m_renderer;
};

