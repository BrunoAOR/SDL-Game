#include "Crosshair.h"

#include "Engine/API/API.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Renderers/Sprite.h"

#include "Behaviours/BehaviourToRemove.h"

void Crosshair::start()
{
	m_alpha = 255;
	sprite = gameObject()->getComponent<Sprite>();
}


void Crosshair::update()
{
	if (InputAPI::getKeyDown(SDL_SCANCODE_L))
	{
		std::weak_ptr<BehaviourToRemove> btr = gameObject()->getComponent<BehaviourToRemove>();
		if (!btr.expired())
		{
			gameObject()->removeComponent(btr);
		}
	}

	if (InputAPI::getKeyDown(SDL_SCANCODE_UP))
	{
		m_alpha += 16;
		if (m_alpha > 255)
		{
			m_alpha = 255;
		}
	}
	if (InputAPI::getKeyDown(SDL_SCANCODE_DOWN))
	{
		m_alpha -= 16;
		if (m_alpha < 0)
		{
			m_alpha = 0;
		}
	}
	
	if (auto lockedSprite = sprite.lock())
	{
		lockedSprite->setAlpha(m_alpha);
	}
}
