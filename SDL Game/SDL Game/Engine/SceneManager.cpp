#include "SceneManager.h"

#include "EngineUtils.cpp"
#include "Scene.h"

std::vector<Scene*> SceneManager::m_scenes;
Scene* SceneManager::m_currentScene = nullptr;


SceneManager::SceneManager()
{

}


bool SceneManager::loadScene(unsigned int index)
{
	if (m_currentScene != nullptr) {
		unloadScene(m_currentScene);
	}

	if (index >= 0 && index < m_scenes.size()) {
		m_currentScene = m_scenes.at(index);
		return m_currentScene->load();
	}
	return false;
}

void SceneManager::close()
{
	if (m_currentScene != nullptr) {
		unloadScene(m_currentScene);
	}
}


void SceneManager::unloadScene(Scene * sceneToUnload)
{
	m_currentScene->unload();
	m_currentScene = nullptr;
}
