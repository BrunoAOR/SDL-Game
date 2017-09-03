#pragma once

#include <string>
#include <SDL.h>

#include "Vector2.h"

class Transform;


class Texture
{
public:
	Texture(SDL_Renderer* renderer);
	~Texture();

	// Loads image at specified path
	bool loadFromFile(std::string path);
	bool loadFromFile(std::string path, Uint32 colorKey);

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	// Set Blend Mode
	void setBlendMode(SDL_BlendMode blendMode);

	// Set alpha modulation
	void setAlpha(Uint8 a);

	// Renders texture at given point
	void render(const Transform* transform, SDL_Rect* clip = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The renderer associated with this texture
	SDL_Renderer* m_renderer;

	// The actual hardware texture
	SDL_Texture* m_texture;

	// Image dimensions
	int m_width;
	int m_height;

	// Help functions
	bool loadFromFile(std::string path, bool shouldColorKey, Uint32 colorKey);
};
