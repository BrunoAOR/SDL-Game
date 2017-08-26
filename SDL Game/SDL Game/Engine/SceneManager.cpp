#include "SceneManager.h"

#include "EngineUtils.cpp"
#include "Scene.h"

std::vector<Scene*> SceneManager::m_scenes;
Scene* SceneManager::m_activeScene = nullptr;


SceneManager::SceneManager()
{

}


bool SceneManager::hasActiveScene()
{
	return m_activeScene != nullptr;
}

bool SceneManager::addGameObject(GameObject * gameObject)
{
	if (m_activeScene == nullptr)
	{
		printf("No active scene in SceneManager\n");
		return false;
	}
	else
	{
		return m_activeScene->addGameObject(gameObject);
	}
}

bool SceneManager::removeGameObject(GameObject * gameObject)
{
	if (m_activeScene == nullptr)
	{
		return false;
	}
	else
	{
		return m_activeScene->removeGameObject(gameObject);
	}
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
	m_activeScene->unloadGameObjects();
	m_activeScene = nullptr;
}
