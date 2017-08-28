#include "Crosshair.h"

#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Texture.h"

#include "BehaviourToRemove.h"

void Crosshair::awake()
{
}

void Crosshair::start()
{
	m_alpha = 255;
}


void Crosshair::update()
{
	if (Input::getKeyDown(SDL_SCANCODE_L))
	{
		BehaviourToRemove* btr = gameObject()->getComponent<BehaviourToRemove>();
		if (btr != nullptr)
		{
			gameObject()->removeComponent(btr);
		}
		// TODO: Get the component of type BehaviourToRemove and call gameObject()->removeBehaviour(Behaviour *) on it to test
	}

	if (Input::getKeyDown(SDL_SCANCODE_UP))
	{
		m_alpha += 16;
		if (m_alpha > 255)
		{
			m_alpha = 255;
		}
	}
	if (Input::getKeyDown(SDL_SCANCODE_DOWN))
	{
		m_alpha -= 16;
		if (m_alpha < 0)
		{
			m_alpha = 0;
		}
	}
	
	gameObject()->texture->setAlpha(m_alpha);
}
