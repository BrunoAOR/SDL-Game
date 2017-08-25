#include "Texture.h"

#include <SDL_image.h>


Texture::Texture(SDL_Renderer* renderer)
{
	// Initialize empty
	m_texture = nullptr;
	m_width = 0;
	m_height = 0;

	// Store renderer reference
	m_renderer = renderer;
}


Texture::~Texture()
{
	// Deallocate
	free();
}


bool Texture::loadFromFile(std::string path)
{
	return loadFromFile(path, false, 0);
}


bool Texture::loadFromFile(std::string path, Uint32 colorKey)
{
	return loadFromFile(path, true, colorKey);
}


bool Texture::loadFromFile(std::string path, bool shouldColorKey, Uint32 colorKey)
{
	// Get rid of previous texture
	free();

	// Load image at specified path as surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Error: Unable to load image at path %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image if required
		if (shouldColorKey)
		{
			if (SDL_SetColorKey(loadedSurface, SDL_TRUE, colorKey) != 0)
			{
				printf("Warning: Unable to color key the loaded image at path %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
		}

		// Create texture from surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (m_texture == nullptr)
		{
			printf("Error: Unable to create texture for image at path %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
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


void Texture::free()
{
	// Free texture if it exists
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}


void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	// Modulate texture color
	SDL_SetTextureColorMod(m_texture, r, g, b);
}


void Texture::setBlendMode(SDL_BlendMode blendMode)
{
	// Set blending function
	SDL_SetTextureBlendMode(m_texture, blendMode);
}


void Texture::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(m_texture, alpha);
}


void Texture::render(int x, int y, SDL_Rect* clip)
{
	// Set the rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_width, m_height };
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(m_renderer, m_texture, clip, &renderQuad);
}


int Texture::getWidth()
{
	return m_width;
}


int Texture::getHeight()
{
	return m_height;
}
