#pragma once

#include <memory>
#include <vector>

class Scene;


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void refreshScenes();
	void loadScene(unsigned int index);
	void close();

	template <typename T>
	bool addScene();
	bool hasActiveScene();

private:
	std::vector<std::shared_ptr<Scene>> m_scenes;
	std::weak_ptr<Scene> m_activeScene;
	std::weak_ptr<Scene> m_sceneToLoad;

	void doLoadScene();
	void unloadScene(std::weak_ptr<Scene> sceneToUnload);
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
