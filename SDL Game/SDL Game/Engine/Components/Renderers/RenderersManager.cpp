#include "RenderersManager.h"

#include <SDL_image.h>
#include "Engine/Components/ComponentType.h"
#include "Engine/globals.h"
#include "Engine/Components/Renderers/Renderer.h"
#include "Engine/Components/Renderers/TextRenderer.h"
#include "Engine/GameObjects/GameObject.h"


RenderersManager::RenderersManager()
	: m_window(nullptr)
	, m_renderer(nullptr)
	, m_font(nullptr)
	, m_fontSize(28)
{
}


RenderersManager::~RenderersManager()
{
}


SDL_Renderer * RenderersManager::getRenderer()
{
	return m_renderer;
}


ComponentType RenderersManager::managedComponentType()
{
	return ComponentType::Renderer;
}


void RenderersManager::update()
{
	// Note: refreshComponents ensures that all weak_ptr in m_components are valid, so locking them is guaranteed to produce a valid shared_ptr
	refreshComponents();

	// Set Render Color to white
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xFF);

	// Clear screen
	SDL_RenderClear(m_renderer);

	for (auto weakRenderer : m_components)
	{
		if (auto renderer = std::static_pointer_cast<Renderer>(weakRenderer.lock()))
		{
			// Actual update
			if (renderer->isActive())
			{
				renderer->render();
			}
		}
	}

	// Update screen
	SDL_RenderPresent(m_renderer);
}


bool RenderersManager::init()
{
	// Success flag
	bool success = true;

	// Create window
	m_window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		printf("Error: Window could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create Renderer for window (used for texture rendering)
		Uint32 flags = SDL_RENDERER_ACCELERATED;
		m_renderer = SDL_CreateRenderer(m_window, -1, flags);
		if (m_renderer == nullptr)
		{
			printf("Error: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create the font
			m_font = TTF_OpenFont("assets/lazy.ttf", m_fontSize);
			if (m_font == nullptr)
			{
				printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}

	return success;
}


void RenderersManager::close()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	TTF_CloseFont(m_font);
	m_font = nullptr;
}


bool RenderersManager::initializeComponent(std::weak_ptr<Component> component)
{
	// At this point, we know that component is a Renderer (or a sub-class there-of)
	if (auto sharedComponent = component.lock())
	{
		auto renderer = std::static_pointer_cast<Renderer>(sharedComponent);
		renderer->m_renderer = m_renderer;

		if (auto textRenderer = std::dynamic_pointer_cast<TextRenderer>(sharedComponent))
		{
			textRenderer->m_font = m_font;
		}
	}
	return false;
}
