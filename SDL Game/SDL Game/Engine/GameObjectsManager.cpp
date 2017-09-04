#include "GameObjectsManager.h"

#include "EngineUtils.h"
#include "GameObject.h"
#include "Behaviour.h"

std::vector<std::shared_ptr<GameObject>> GameObjectsManager::m_gameObjects;
std::vector<std::shared_ptr<GameObject>> GameObjectsManager::m_gosToAdd;
std::vector<std::weak_ptr<GameObject>> GameObjectsManager::m_gosToDestroy;

GameObjectsManager::GameObjectsManager()
{
}


void GameObjectsManager::updateGameObjectsAndBehaviours()
{
	refreshGameObjects();

	for (auto go : m_gameObjects)
	{
		if (go->isActive())
		{
			for (auto b : go->m_behaviours)
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


void GameObjectsManager::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (indexOf(m_gosToAdd, gameObject) == -1) {
		m_gosToAdd.push_back(gameObject);
	}
	
}


void GameObjectsManager::destroyGameObject(std::weak_ptr<GameObject> gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (indexOf(m_gosToDestroy, gameObject) == -1) {
		m_gosToDestroy.push_back(gameObject);
	}
}

void GameObjectsManager::destroyAllGameObjects()
{
	m_gameObjects.clear();
}


void GameObjectsManager::refreshGameObjects()
{
	// Delete GOs
	for (auto go : m_gosToDestroy)
	{
		doDestroyGameObject(go);
	}	
	m_gosToDestroy.clear();
	
	// Add new GOs
	for (auto go : m_gosToAdd)
	{
		doAddGameObject(go);
	}
	m_gosToAdd.clear();

	// Refresh all GOs (this will finish initializing the newly added GOs
	for (auto go : m_gameObjects)
	{
		go->refreshComponents();
	}	
}


void GameObjectsManager::doAddGameObject(std::shared_ptr<GameObject> gameObject)
{
	if (indexOf(m_gameObjects, gameObject) == -1) {
		// So the gameObject hasn't previously been added
		m_gameObjects.push_back(gameObject);
	}
}


void GameObjectsManager::doDestroyGameObject(std::weak_ptr<GameObject> gameObject)
{
	int index = indexOf(m_gameObjects, gameObject.lock());
	if (index != -1) {
		// So, the gameObject is in the gameObjects vector
		// Destroy children first
		doDestroyChildren(gameObject);
		m_gameObjects.erase(m_gameObjects.begin() + index);
	}
}

void GameObjectsManager::doDestroyChildren(std::weak_ptr<GameObject> parentGameObject)
{
	for (auto weakChildGO : parentGameObject.lock()->m_children)
	{
		if (auto childGO = weakChildGO.lock())
		{
			doDestroyChildren(weakChildGO);
			int index = indexOf(m_gameObjects, childGO);
			if (index != -1) {
				// So, the gameObject is in the gameObjects vector
				m_gameObjects.erase(m_gameObjects.begin() + index);
			}
		}

	}
}


