#include "SpawnedCrosshair.h"

#include "Engine/GameObject.h"


void SpawnedCrosshair::start()
{
	m_wentRight = false;
}


void SpawnedCrosshair::update()
{
	auto transform = gameObject()->transform.lock();
	Vector2 currentPos = transform->getLocalPosition();
	if (!m_wentRight) {
		currentPos.x -= 16;
		transform->setWorldPosition(currentPos);
		m_wentRight = true;
	}
	else
	{
		currentPos.x += 16;
		transform->setWorldPosition(currentPos);
		m_wentRight = false;
	}
}
