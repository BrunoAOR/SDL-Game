#pragma once

#include <memory>
#include <vector>

class GameObject;
class Transform;


class GameObjectsManager
{
public:
	GameObjectsManager();
	~GameObjectsManager();

	void update();
	void addGameObject(std::shared_ptr<GameObject> gameObject);
	void destroyGameObject(std::weak_ptr<GameObject> gameObject);
	void destroyAllGameObjects();
	
private:
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
	std::vector<std::shared_ptr<GameObject>> m_gosToAdd;
	std::vector<std::weak_ptr<GameObject>> m_gosToDestroy;

	void refreshGameObjects();
	void doAddGameObject(std::shared_ptr<GameObject> gameObject);
	void doDestroyGameObject(std::weak_ptr<GameObject> gameObject);
	void doDestroyChildren(Transform* transform);
};

