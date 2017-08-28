#include "SceneManager.h"

#include "EngineUtils.h"
#include "Scene.h"
#include "GameObjectsManager.h"

std::vector<Scene*> SceneManager::m_scenes;
Scene* SceneManager::m_activeScene = nullptr;


SceneManager::SceneManager()
{

}


bool SceneManager::hasActiveScene()
{
	return m_activeScene != nullptr;
}


bool SceneManager::loadScene(unsigned int index)
{
	if (m_activeScene != nullptr)
	{
		unloadScene(m_activeScene);
	}

	if (index >= 0 && index < m_scenes.size())
	{
		// Set scene as active
		m_activeScene = m_scenes.at(index);
		// Load scene
		return m_activeScene->load();
	}
	return false;
}


void SceneManager::close()
{
	if (m_activeScene != nullptr)
	{
		unloadScene(m_activeScene);
	}
}


void SceneManager::unloadScene(Scene * sceneToUnload)
{
	m_activeScene->unload();
	GameObjectsManager::destroyAllGameObjects();
	m_activeScene = nullptr;
}
