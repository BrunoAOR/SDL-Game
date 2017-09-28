#include "RenderersManager.h"

#include <SDL_image.h>
#include "Engine/constants.h"
#include "Engine/Components/Renderers/Renderer.h"
#include "Engine/GameObjects/GameObject.h"


RenderersManager::RenderersManager()
{
}


RenderersManager::~RenderersManager()
{
}


SDL_Renderer * RenderersManager::getRenderer()
{
	return m_renderer;
}


bool RenderersManager::init()
{
	// Success flag
	bool success = true;

	// Create window
	m_window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	}

	return success;
}


void RenderersManager::close()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
}


bool RenderersManager::canManage(std::weak_ptr<Component> component)
{
	if (std::dynamic_pointer_cast<Renderer>(component.lock()))
	{
		return true;
	}
	else
	{
		return false;
	}
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


bool RenderersManager::initializeComponent(std::weak_ptr<Component> component)
{
	if (auto sharedComponent = component.lock())
	{
		if (auto renderer = std::dynamic_pointer_cast<Renderer>(sharedComponent))
		{
			renderer->m_renderer = m_renderer;
			return true;
		}
	}
	return false;
}