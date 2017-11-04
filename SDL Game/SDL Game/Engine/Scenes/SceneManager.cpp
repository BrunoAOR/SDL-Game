#include "SceneManager.h"

#include "Engine/Engine.h"
#include "Engine/EngineUtils.h"
#include "Engine/Scenes/Scene.h"
#include "Engine/GameObjects/GameObjectsManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
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
		engine->gameObjectsManager->destroyAllGameObjects();
	}
}
