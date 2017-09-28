#pragma once

#include "Engine/Components/Renderers/Renderer.h"


class Sprite :
	public Renderer
{
public:
	Sprite();
	~Sprite();

	// Inherited via Renderer
	virtual void render() override;
};

