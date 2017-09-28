#pragma once

#include <memory>
#include <vector>

class Scene;


class SceneManager
{
public:
	static void refreshScenes();
	static void loadScene(unsigned int index);
	static void close();

	template <typename T>
	static bool addScene();
	static bool hasActiveScene();

private:
	SceneManager();
	static std::vector<std::shared_ptr<Scene>> m_scenes;
	static std::weak_ptr<Scene> m_activeScene;
	static std::weak_ptr<Scene> m_sceneToLoad;

	static void doLoadScene();
	static void unloadScene(std::weak_ptr<Scene> sceneToUnload);
};

template<typename T>
bool SceneManager::addScene()
{
	// Success flag
	bool success = true;

	if (std::is_base_of<Scene, T>::value && !std::is_same<Scene, T>::value)
	{
		auto scene = std::make_shared<T>();
		m_scenes.push_back(scene);
	}
	else
	{
		success = false;
		printf("Error, can't attach selected class as a scene!");
	}

	return success;
}
