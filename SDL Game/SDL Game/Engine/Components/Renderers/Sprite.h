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
};

