#pragma once

#include <vector>

class GameObject;
class Behaviour;


class GameObjectsManager
{
public:
	static void updateGameObjectsAndBehaviours();
	static void addGameObject(GameObject* gameObject);
	static void destroyGameObject(GameObject* gameObject);
	static void destroyAllGameObjects();
	
private:
	GameObjectsManager();
	static std::vector<GameObject *> m_gameObjects;
	static std::vector<GameObject *> m_gosToAdd;
	static std::vector<GameObject *> m_gosToDestroy;

	static void refreshGameObjects();
	static void doAddGameObject(GameObject* gameObject);
	static void doDestroyGameObject(GameObject* gameObject);
};

