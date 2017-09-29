#include "TextRenderer.h"

#include <SDL_ttf.h> 


TextRenderer::TextRenderer()
	: m_font(nullptr)
	, m_text("")
	, m_color(SDL_Color{ 255, 255, 255, 255 })
	, m_shouldReloadTexture(true)
{
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::setText(const std::string & text)
{
	if (m_text != text)
	{
		m_text = text;
		m_shouldReloadTexture = true;
	}
}

void TextRenderer::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	if (m_color.r != r || m_color.g != g || m_color.b != b)
	{
		m_color = { r, g, b, 255 };
		m_shouldReloadTexture = true;
	}
}


bool TextRenderer::loadTexture()
{
	if (m_font == nullptr)
	{
		return false;
	}

	// Get rid of previous texture
	free();

	// Render text surface
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
	if (loadedSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (m_texture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Store image dimension
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		// Free the loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return m_texture != nullptr;
}

void TextRenderer::render()
{
	if (m_shouldReloadTexture)
	{
		loadTexture();
		m_shouldReloadTexture = false;
	}
	renderMain();
}
