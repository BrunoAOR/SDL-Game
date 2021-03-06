#pragma once

#include <SDL_render.h>
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
	// The renderer associated with this texture
	SDL_Renderer* m_renderer;

	// The actual hardware texture
	SDL_Texture* m_texture;

	// Image dimensions
	int m_width;
	int m_height;

	// Renders texture at given point
	void renderMain(SDL_Rect* clip = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void free();

private:
	// Pivots
	Vector2 m_positionPivot;
	Vector2 m_rotationPivot;
	Vector2 m_scalePivot;
};
