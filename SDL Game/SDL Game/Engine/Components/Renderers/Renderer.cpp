#include "Renderer.h"

#include <SDL_image.h>
#include "Engine/constants.h"
#include "Engine/Components/Renderers/RenderersManager.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"

Renderer::Renderer()
	: m_renderer(nullptr)
	, m_texture(nullptr)
	, m_width(0)
	, m_height(0)
	, m_positionPivot(Vector2(0.5, 0.5))
	, m_rotationPivot(Vector2(0.5, 0.5))
	, m_scalePivot(Vector2(0.5, 0.5))
{
}


Renderer::~Renderer()
{
	// Deallocate texture
	free();
}


void Renderer::free()
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


bool Renderer::loadImage(std::string path)
{
	return loadImage(path, false, 0);
}

bool Renderer::loadImage(std::string path, Uint32 colorKey)
{
	return loadImage(path, true, colorKey);
}


bool Renderer::loadImage(std::string path, bool shouldColorKey, Uint32 colorKey)
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


void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	// Modulate texture color
	if (m_texture != nullptr) {
		SDL_SetTextureColorMod(m_texture, r, g, b);
	}
}


void Renderer::setBlendMode(SDL_BlendMode blendMode)
{
	// Set blending function
	if (m_texture != nullptr) {
		SDL_SetTextureBlendMode(m_texture, blendMode);
	}
}


void Renderer::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	if (m_texture != nullptr) {
		SDL_SetTextureAlphaMod(m_texture, alpha);
	}
}


int Renderer::getWidth()
{
	return m_width;
}


int Renderer::getHeight()
{
	return m_height;
}


void Renderer::renderMain(SDL_Rect* clip, SDL_RendererFlip flip)
{
	// Note: All transform pivots are transformed to "(1 - pivot) for the y axis so that the zero refers to the bottom of the RenderQuad"
	Transform* transform = gameObject()->transform.lock().get();

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


// PIVOTS


Vector2 Renderer::getPositionPivot() const
{
	return m_positionPivot;
}


void Renderer::setPositionPivot(const Vector2& positionPivot)
{
	m_positionPivot = positionPivot;
}


Vector2 Renderer::getRotationPivot() const
{
	return m_rotationPivot;
}


void Renderer::setRotationPivot(const Vector2& rotationPivot)
{
	m_rotationPivot = rotationPivot;
}


Vector2 Renderer::getScalePivot() const
{
	return m_scalePivot;
}


void Renderer::setScalePivot(const Vector2& scalePivot)
{
	m_scalePivot = scalePivot;
}


void Renderer::setAllPivots(const Vector2& pivot)
{
	setPositionPivot(pivot);
	setRotationPivot(pivot);
	setScalePivot(pivot);
}