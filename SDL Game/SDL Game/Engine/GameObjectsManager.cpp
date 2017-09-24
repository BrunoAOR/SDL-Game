#include "GameObjectsManager.h"

#include "EngineUtils.h"
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"

std::vector<std::shared_ptr<GameObject>> GameObjectsManager::m_gameObjects;
std::vector<std::shared_ptr<GameObject>> GameObjectsManager::m_gosToAdd;
std::vector<std::weak_ptr<GameObject>> GameObjectsManager::m_gosToDestroy;

GameObjectsManager::GameObjectsManager()
{
}


void GameObjectsManager::update()
{
	refreshGameObjects();
}


void GameObjectsManager::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (EngineUtils::indexOf(m_gosToAdd, gameObject) == -1) {
		m_gosToAdd.push_back(gameObject);
	}
	
}


void GameObjectsManager::destroyGameObject(std::weak_ptr<GameObject> gameObject)
{
	// Check if the gameObject hasn't already been added to the list
	if (EngineUtils::indexOf(m_gosToDestroy, gameObject) == -1) {
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
	if (EngineUtils::indexOf(m_gameObjects, gameObject) == -1) {
		// So the gameObject hasn't previously been added
		m_gameObjects.push_back(gameObject);
	}
}


void GameObjectsManager::doDestroyGameObject(std::weak_ptr<GameObject> gameObject)
{
	if (auto go = gameObject.lock())
	{
		int index = EngineUtils::indexOf(m_gameObjects, go);
		if (index != -1) {
			// So, the gameObject is in the gameObjects vector
			// Destroy children first
			if (auto go = gameObject.lock())
			{
				doDestroyChildren(gameObject.lock()->transform.lock().get());
			}
			// Now find the updated index, since destroying the children has modified the actual index
			int newIndex = EngineUtils::indexOf(m_gameObjects, go);
			m_gameObjects.erase(m_gameObjects.begin() + newIndex);
		}
	}
}

void GameObjectsManager::doDestroyChildren(Transform* parentTransform)
{
	auto go = parentTransform->gameObject().get();
	for (Transform* childTransform : parentTransform->m_children)
	{
		doDestroyChildren(childTransform);
		int index = EngineUtils::indexOf(m_gameObjects, childTransform->gameObject());
		if (index != -1) {
			// So, the gameObject is in the gameObjects vector
			m_gameObjects.erase(m_gameObjects.begin() + index);
		}
	}

}


