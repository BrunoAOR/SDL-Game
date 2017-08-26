#include "Scene.h"

#include "EngineUtils.cpp"
#include "GameObject.h"


Scene::~Scene()
{
	unloadGameObjects();
}

bool Scene::addGameObject(GameObject * gameObject)
{
	int index = indexOf(m_gameObjects, gameObject);
	if (index == -1)
	{
		m_gameObjects.push_back(gameObject);
		return true;
	}
	return false;
}

bool Scene::removeGameObject(GameObject * gameObject)
{
	int index = indexOf(m_gameObjects, gameObject);
	if (index != -1)
	{
		m_gameObjects.erase(m_gameObjects.begin() + index);
		return true;
	}
	else
	{
		return false;
	}
}

void Scene::unloadGameObjects()
{
	for (GameObject* go : m_gameObjects)
	{
		delete go;
	}
	m_gameObjects.clear();
}
