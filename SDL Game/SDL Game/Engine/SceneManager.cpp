#include "SceneManager.h"

#include "EngineUtils.h"
#include "Scene.h"
#include "GameObjectsManager.h"

std::vector<std::shared_ptr<Scene>> SceneManager::m_scenes;
std::weak_ptr<Scene> SceneManager::m_activeScene;
std::weak_ptr<Scene> SceneManager::m_sceneToLoad;


SceneManager::SceneManager()
{

}


bool SceneManager::hasActiveScene()
{
	return !m_activeScene.expired();
}


void SceneManager::refreshScenes()
{
	if (!m_sceneToLoad.expired())
	{
		doLoadScene();
	}
}

void SceneManager::loadScene(unsigned int index)
{
	if (index >= 0 && index < m_scenes.size())
	{
		m_sceneToLoad = m_scenes.at(index);
	}
}


void SceneManager::close()
{
	if (m_activeScene.lock())
	{
		unloadScene(m_activeScene);
	}
	m_scenes.clear();
}


void SceneManager::doLoadScene()
{
	if (m_sceneToLoad.expired())
	{
		return;
	}

	if (!m_activeScene.expired())
	{
		unloadScene(m_activeScene);
		m_activeScene.reset();
	}
	// Set scene as active
	m_activeScene = m_sceneToLoad;
	// reset m_sceneToLoad
	m_sceneToLoad.reset();
	// Load scene
	m_activeScene.lock()->load();
}

void SceneManager::unloadScene(std::weak_ptr<Scene> sceneToUnload)
{
	if (auto scene = sceneToUnload.lock())
	{
		scene->unload();
		GameObjectsManager::destroyAllGameObjects();
	}
}
