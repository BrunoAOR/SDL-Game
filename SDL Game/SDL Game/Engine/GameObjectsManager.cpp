#include "GameObjectsManager.h"

#include "EngineUtils.h"
#include "GameObject.h"
#include "Behaviour.h"


std::vector<GameObject *> GameObjectsManager::m_gameObjects;
std::vector<GameObject *> GameObjectsManager::m_gosToAdd;
std::vector<GameObject *> GameObjectsManager::m_gosToDestroy;


GameObjectsManager::GameObjectsManager()
{
}


void GameObjectsManager::updateGameObjectsAndBehaviours()
{
	refreshGameObjects();

	for (GameObject* go : m_gameObjects)
	{
		if (go->isActive())
		{
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
		}
	}
}


void GameObjectsManager::addGameObject(GameObject * gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (indexOf(m_gosToAdd, gameObject) == -1) {
		m_gosToAdd.push_back(gameObject);
	}
	
}


void GameObjectsManager::destroyGameObject(GameObject * gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (indexOf(m_gosToDestroy, gameObject) == -1) {
		m_gosToDestroy.push_back(gameObject);
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
		go->refreshComponents();
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
