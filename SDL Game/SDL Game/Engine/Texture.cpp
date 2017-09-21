#include "Texture.h"

#include <SDL_image.h>
#include "constants.h"
#include "Transform.h"

Texture::Texture(SDL_Renderer* renderer)
	: m_positionPivot(Vector2(0.5, 0.5))
	, m_rotationPivot(Vector2(0.5, 0.5))
	, m_scalePivot(Vector2(0.5,0.5))
	// Initialize empty
	, m_texture(nullptr)
	, m_width(0)
	, m_height(0)
	// Store renderer reference
	, m_renderer(renderer)
{

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


void Texture::render(const Transform* const transform, SDL_Rect* clip, SDL_RendererFlip flip)
{
	// Note: All transform pivots are transformed to "(1 - pivot) for the y axis so that the zero refers to the bottom of the RenderQuad"

	// Extract info from the transform
	Vector2 pos = transform->getWorldPosition();
	double rot = transform->getWorldRotation();
	Vector2 sca = transform->getWorldScale();

	// Correct the position and rotations to simulate a reference system with 0 in the bottom-left,
	// x increasing to the right (same as SDL) and Y increasing up (opposite of SDL)
	pos.y = constants::SCREEN_HEIGHT - pos.y;
	rot *= -1;

	// Calculate the texture size, clipped if required
	Vector2 rawSize;
	if (clip)
	{
		rawSize = { (double)clip->w, (double)clip->h };
	}
	else
	{
		rawSize = { (double)m_width, (double)m_height };
	}

	// Set the rendering space based on the position and positionPivot
	SDL_Rect renderQuad =
	{
		(int)(pos.x - m_positionPivot.x * rawSize.x),
		(int)(pos.y - (1 - m_positionPivot.y) * rawSize.y),
		(int)rawSize.x,
		(int)rawSize.y
	};
	
	// Modify for the scale and scalePivot
	renderQuad.x = (int)(renderQuad.x - m_scalePivot.x * (sca.x - 1) * rawSize.x);
	renderQuad.y = (int)(renderQuad.y - (1 - m_scalePivot.y) * (sca.y - 1) * rawSize.y);
	renderQuad.w = (int)(renderQuad.w * sca.x);
	renderQuad.h = (int)(renderQuad.h * sca.y);
	
	// Calculate the center of rotation based on the rotationPivot
	Vector2 scaledSize = { rawSize.x * sca.x , rawSize.y * sca.y };
	SDL_Point center =
	{
		(int)(m_rotationPivot.x * scaledSize.x),
		(int)((1 - m_rotationPivot.y) * scaledSize.y)
	};

	// Correct issue with texture not being rendered if the renderQuad has negative width or height and there is no rotation
	// Solution: add a tiny rotation
	if (rot == 0 && (sca.x < 0 || sca.y<0))
	{
		rot = FLT_EPSILON;
	}

	SDL_RenderCopyEx(m_renderer, m_texture, clip, &renderQuad, rot, &center, flip);
}


int Texture::getWidth()
{
	return m_width;
}


int Texture::getHeight()
{
	return m_height;
}


// PIVOTS


Vector2 Texture::getPositionPivot() const
{
	return m_positionPivot;
}


void Texture::setPositionPivot(const Vector2& positionPivot, bool adjustScalePivot)
{
	m_positionPivot = positionPivot;

	if (adjustScalePivot)
	{
		setScalePivot(m_positionPivot);
	}
}


Vector2 Texture::getRotationPivot() const
{
	return m_rotationPivot;
}


void Texture::setRotationPivot(const Vector2& rotationPivot)
{
	m_rotationPivot = rotationPivot;
}


Vector2 Texture::getScalePivot() const
{
	return m_scalePivot;
}


void Texture::setScalePivot(const Vector2& scalePivot)
{
	m_scalePivot = scalePivot;
}


void Texture::setAllPivots(const Vector2& pivot)
{
	setPositionPivot(pivot);
	setRotationPivot(pivot);
	setScalePivot(pivot);
}