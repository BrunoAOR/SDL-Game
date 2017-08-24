#pragma once

#include <vector>

class GameObject;


class RenderManager
{
public:
	static void update();
	static void subscribeGameObject(GameObject* gameObject);
	static void unsubscribeGameObject(GameObject* gameObject);

private:
	RenderManager();
	static std::vector<GameObject *> gameObjects;
};

