#pragma once

#include <SDL.h>
#include <string>
#include "Engine/Components/Component.h"
#include "Engine/Vector2.h"


class Renderer :
	public Component
{
	friend class RenderersManager;

public:
	Renderer();
	virtual ~Renderer() = 0;

	virtual void render() = 0;

	bool loadImage(std::string path);
	bool loadImage(std::string path, Uint32 colorKey);

	// Set color modulation
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	// Set Blend Mode
	void setBlendMode(SDL_BlendMode blendMode);

	// Set alpha modulation
	void setAlpha(Uint8 a);

	// Get dimensions
	int getWidth();
	int getHeight();

	// Pivots
	Vector2 getPositionPivot() const;
	void setPositionPivot(const Vector2& positionPivot);

	Vector2 getRotationPivot() const;
	void setRotationPivot(const Vector2& rotationPivot);

	Vector2 getScalePivot() const;
	void setScalePivot(const Vector2& scalePivot);

	void setAllPivots(const Vector2& pivot);

protected:
	// Renders texture at given point
	void renderMain(SDL_Rect* clip = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	// The renderer associated with this texture
	SDL_Renderer* m_renderer;

	// The actual hardware texture
	SDL_Texture* m_texture;

	// Image dimensions
	int m_width;
	int m_height;

	void free();
	bool loadImage(std::string path, bool shouldColorKey, Uint32 colorKey);

	// Pivots
	Vector2 m_positionPivot;
	Vector2 m_rotationPivot;
	Vector2 m_scalePivot;
};
