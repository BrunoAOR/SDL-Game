#pragma once

#include <memory>
#include <vector>

class GameObject;


class GameObjectsManager
{
public:
	static void update();
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
	static void doDestroyChildren(std::weak_ptr<GameObject> parentGameObject);
};

