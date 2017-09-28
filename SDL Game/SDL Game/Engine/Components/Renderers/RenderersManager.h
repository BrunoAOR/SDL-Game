#pragma once

#include <SDL.h>
#include "Engine/Components/ComponentManager.h"

class Component;


class RenderersManager final :
	public ComponentManager
{
	friend class ComponentsManager;
public:
	~RenderersManager();
	
	// Inherited via ComponentManager
	virtual bool canManage(std::weak_ptr<Component> component) override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(std::weak_ptr<Component> component) override;


private:
	RenderersManager();
	SDL_Window * m_window;
	SDL_Renderer * m_renderer;

	SDL_Renderer * getRenderer();
};
