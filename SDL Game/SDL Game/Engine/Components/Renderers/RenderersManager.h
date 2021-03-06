#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Engine/Components/ComponentManager.h"

class Component;


class RenderersManager final :
	public ComponentManager
{
	friend class ComponentsManager;
public:
	~RenderersManager();

private:
	RenderersManager();
	SDL_Window * m_window;
	SDL_Renderer * m_renderer;
	TTF_Font * m_font;
	int m_fontSize;

	SDL_Renderer * getRenderer();

	// Inherited via ComponentManager
	virtual ComponentType managedComponentType() override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(std::weak_ptr<Component> component) override;
};
