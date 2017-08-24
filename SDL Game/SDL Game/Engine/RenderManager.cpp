#include "RenderManager.h"

#include "EngineUtils.cpp"
#include "GameObject.h"
#include "Texture.h"

std::vector<GameObject *> RenderManager::gameObjects;

RenderManager::RenderManager()
{
}


void RenderManager::update()
{
	for (GameObject* go : gameObjects)
	{
		go->texture->render((int)go->transform.position.x, (int)go->transform.position.y);
	}
}

void RenderManager::subscribeGameObject(GameObject * gameObject)
{
	if (indexOf(gameObjects, gameObject) == -1) {
		// So the gameObject hasn't previously been added
		gameObjects.push_back(gameObject);
	}
}

void RenderManager::unsubscribeGameObject(GameObject * gameObject)
{
	int index = indexOf(gameObjects, gameObject);
	if (index != -1) {
		// So, the behaviour is in the behaviours vector
		gameObjects.erase(gameObjects.begin() + index);
	}
}

