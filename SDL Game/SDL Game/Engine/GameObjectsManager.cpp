#include "GameObjectsManager.h"

#include "EngineUtils.cpp"
#include "GameObject.h"
#include "Behaviour.h"


std::vector<GameObject *> GameObjectsManager::m_gameObjects;
std::vector<GameObject *> GameObjectsManager::m_gosToAdd;
std::vector<GameObject *> GameObjectsManager::m_gosToDestroy;
bool GameObjectsManager::m_isUpdating = false;


GameObjectsManager::GameObjectsManager()
{
}


void GameObjectsManager::updateBehaviours()
{
	refreshGameObjects();
	m_isUpdating = true;
	for (GameObject* go : m_gameObjects)
	{
		go->refreshBehaviours();
		if (go->isActive())
		{
			go->m_isUpdating = true;
			for (Behaviour* b : go->m_behaviours)
			{
				if (!b->m_started) {
					b->start();
					b->m_started = true;
				}
				else
				{
					b->update();
				}
			}
			go->m_isUpdating = false;
		}
	}
	m_isUpdating = false;
}


void GameObjectsManager::addGameObject(GameObject * gameObject)
{
	if (m_isUpdating)
	{
		if (indexOf(m_gosToAdd, gameObject) == -1) {
			m_gosToAdd.push_back(gameObject);
		}
	}
	else
	{
		doAddGameObject(gameObject);
	}
}


void GameObjectsManager::destroyGameObject(GameObject * gameObject)
{
	if (m_isUpdating)
	{
		if (indexOf(m_gosToDestroy, gameObject) == -1) {
			m_gosToDestroy.push_back(gameObject);
		}
	}
	else
	{
		doDestroyGameObject(gameObject);
	}
}

void GameObjectsManager::destroyAllGameObjects()
{
	for (GameObject* go : m_gameObjects)
	{
		delete go;
	}
	m_gameObjects.clear();
}


void GameObjectsManager::refreshGameObjects()
{
	for (GameObject* go : m_gameObjects)
	{
		go->refreshBehaviours();
	}
	for (GameObject* go : m_gosToAdd)
	{
		doAddGameObject(go);
	}
	m_gosToAdd.clear();

	for (GameObject* go : m_gosToDestroy)
	{
		doDestroyGameObject(go);
	}
	m_gosToDestroy.clear();
}


void GameObjectsManager::doAddGameObject(GameObject * gameObject)
{
	if (indexOf(m_gameObjects, gameObject) == -1) {
		// So the gameObject hasn't previously been added
		m_gameObjects.push_back(gameObject);
	}
}


void GameObjectsManager::doDestroyGameObject(GameObject * gameObject)
{
	int index = indexOf(m_gameObjects, gameObject);
	if (index != -1) {
		// So, the behaviour is in the behaviours vector
		m_gameObjects.erase(m_gameObjects.begin() + index);
		delete gameObject;
	}
}
