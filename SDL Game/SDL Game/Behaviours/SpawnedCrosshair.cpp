#include "SpawnedCrosshair.h"

#include "Engine/GameObject.h"


void SpawnedCrosshair::start()
{
	m_wentRight = false;
}


void SpawnedCrosshair::update()
{
	Vector2 currentPos = gameObject()->transform.getLocalPosition();
	if (!m_wentRight) {
		currentPos.x -= 16;
		gameObject()->transform.setWorldPosition(currentPos);
		m_wentRight = true;
	}
	else
	{
		currentPos.x += 16;
		gameObject()->transform.setWorldPosition(currentPos);
		m_wentRight = false;
	}
}
