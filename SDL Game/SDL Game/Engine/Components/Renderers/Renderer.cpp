#include "Renderer.h"

#include "Engine/globals.h"
#include "Engine/Components/Renderers/RenderersManager.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Components/ComponentType.h"


Renderer::Renderer()
	: m_renderer(nullptr)
	, m_texture(nullptr)
	, m_width(0)
	, m_height(0)
	, m_positionPivot(Vector2(0.5, 0.5))
	, m_rotationPivot(Vector2(0.5, 0.5))
	, m_scalePivot(Vector2(0.5, 0.5))
{
	type = ComponentType::Renderer;
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
	if (m_renderer == nullptr || m_texture == nullptr)
	{
		return;
	}

	auto sharedTransform = gameObject()->transform.lock();
	if (!sharedTransform)
	{
		return;
	}

	// Extract info from the transform
	Vector2 pos = sharedTransform->getWorldPosition();
	double rot = sharedTransform->getWorldRotation();
	Vector2 sca = sharedTransform->getWorldScale();

	// Correct the position and rotations to simulate a reference system with 0 in the bottom-left,
	// x increasing to the right (same as SDL) and Y increasing up (opposite of SDL)
	pos.y = SCREEN_HEIGHT - pos.y;
	rot *= -1;

	// Calculate the raw size, clipped if required
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
	double renderQuadX = pos.x - m_positionPivot.x * rawSize.x;
	double renderQuadY = pos.y - (1 - m_positionPivot.y) * rawSize.y;
	double renderQuadW = rawSize.x;
	double renderQuadH = rawSize.y;

	// Modify for the gameObject scale and scalePivot
	SDL_Rect renderQuad = 
	{
	(int)round(renderQuadX - m_scalePivot.x * (sca.x - 1) * rawSize.x),
	(int)round(renderQuadY - (1 - m_scalePivot.y) * (sca.y - 1) * rawSize.y),
	(int)round(renderQuadW * sca.x),
	(int)round(renderQuadH * sca.y)
	};
	// Calculate the center of rotation based on the rotationPivot
	Vector2 scaledSize = { rawSize.x * sca.x , rawSize.y * sca.y };
	SDL_Point center =
	{
		(int)round(m_rotationPivot.x * scaledSize.x),
		(int)round((1 - m_rotationPivot.y) * scaledSize.y)
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
