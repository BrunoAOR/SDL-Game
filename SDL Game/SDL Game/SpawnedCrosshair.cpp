#include "SpawnedCrosshair.h"

#include "Engine/GameObject.h"

void SpawnedCrosshair::start()
{
	m_wentRight = false;
}


void SpawnedCrosshair::update()
{
	if (!m_wentRight) {
		gameObject()->transform.position.x -= 16;
		m_wentRight = true;
	}
	else
	{
		gameObject()->transform.position.x += 16;
		m_wentRight = false;
	}
}
