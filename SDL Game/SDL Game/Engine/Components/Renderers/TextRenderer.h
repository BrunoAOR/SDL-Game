#pragma once

#include "Engine/Components/Renderers/Renderer.h"
#include <SDL_ttf.h>

class TextRenderer final :
	public Renderer
{
	friend class RenderersManager;
public:
	TextRenderer();
	~TextRenderer();

	void setText(const std::string & text);
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	// Inherited via Renderer
	virtual void render() override;

private:
	TTF_Font * m_font;
	std::string m_text;
	SDL_Color m_color;
	bool m_shouldReloadTexture;
	
	bool loadTexture();
};

