#pragma once

#include <vector>

class Scene;

class SceneManager
{
public:
	static bool loadScene(unsigned int index);
	static void close();

	template <typename T>
	static bool addScene();

private:
	SceneManager();
	static std::vector<Scene*> m_scenes;
	static Scene* m_currentScene;

	static void unloadScene(Scene* sceneToUnload);
};

template<typename T>
bool SceneManager::addScene()
{
	// Success flag
	bool success = true;

	if (std::is_base_of<Scene, T>::value) {
		T* scene = new T();
		m_scenes.push_back(scene);
	}
	else {
		success = false;
		printf("Error, can't attach selected class as a scene!");
	}

	return success;
}
