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
	void render(const Transform* const transform, SDL_Rect* clip = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

	// Pivots
	Vector2 getPositionPivot() const;
	void setPositionPivot(const Vector2& positionPivot, bool adjustScalePivot = true);

	Vector2 getRotationPivot() const;
	void setRotationPivot(const Vector2& rotationPivot);

	Vector2 getScalePivot() const;
	void setScalePivot(const Vector2& scalePivot);

	void setAllPivots(const Vector2& pivot);

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

	// Pivots
	Vector2 m_positionPivot;
	Vector2 m_rotationPivot;
	Vector2 m_scalePivot;
};
