#pragma once

#include "Engine/Components/Renderers/SpriteRenderer.h"


class Sprite final:
	public SpriteRenderer
{
public:
	Sprite();
	~Sprite();

	// Inherited via Renderer
	virtual void render() override;

	void setClipRect(SDL_Rect rect);
	SDL_Rect getClipRect();
	void resetClipRect();

private:
	bool m_hasClipRect = false;
	SDL_Rect m_clipRect;
};

