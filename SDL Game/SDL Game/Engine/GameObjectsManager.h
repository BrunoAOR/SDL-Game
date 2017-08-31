#pragma once

#include <memory>
#include <vector>
#include "GameObject.h"


class Behaviour;


class GameObjectsManager
{
public:
	static void updateGameObjectsAndBehaviours();
	static void addGameObject(std::shared_ptr<GameObject> gameObject);
	static void destroyGameObject(std::weak_ptr<GameObject> gameObject);
	static void destroyAllGameObjects();
	
private:
	GameObjectsManager();
	static std::vector<std::shared_ptr<GameObject>> m_gameObjects;
	static std::vector<std::shared_ptr<GameObject>> m_gosToAdd;
	static std::vector<std::weak_ptr<GameObject>> m_gosToDestroy;

	static void refreshGameObjects();
	static void doAddGameObject(std::shared_ptr<GameObject> gameObject);
	static void doDestroyGameObject(std::weak_ptr<GameObject> gameObject);
};
