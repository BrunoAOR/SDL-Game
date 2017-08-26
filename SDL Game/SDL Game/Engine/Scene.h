#pragma once

#include <vector>

class SceneManager;
class GameObject;

class Scene
{
	friend class SceneManager;
public:
	virtual ~Scene();
	virtual bool load() = 0;
	virtual void unload() = 0;

private:
	std::vector<GameObject *> m_gameObjects;
	
	bool addGameObject(GameObject* gameObject);
	bool removeGameObject(GameObject* gameObject);
	void unloadGameObjects();
};
