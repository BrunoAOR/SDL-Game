#include "GameObject.h"

#include "EngineUtils.cpp"
#include "Texture.h"
#include "Behaviour.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "GameObjectsManager.h"


GameObject::GameObject()
{
	// Initialize texture empty
	texture = nullptr;

	m_isActive = true;
	m_isUpdating = false;
}


GameObject::~GameObject()
{
	removeTexture();
	for (Behaviour* b : m_behaviours)
	{
		delete b;
	}
	m_behaviours.clear();
}


bool GameObject::addTexture(std::string path)
{
	removeTexture();
	texture = RenderManager::createTexture(path);

	if (texture != nullptr)
	{
		RenderManager::subscribeGameObject(this);
	}
	return texture != nullptr;
}


void GameObject::removeTexture()
{
	if (texture != nullptr)
	{
		texture->free();
		delete texture;
		texture = nullptr;
		RenderManager::unsubscribeGameObject(this);
	}
}


void GameObject::refreshBehaviours()
{
	for (Behaviour* b : m_behavioursToAdd)
	{
		doAddBehaviour(b);
	}
	m_behavioursToAdd.clear();
	for (Behaviour* b : m_behavioursToRemove)
	{
		doRemoveBehaviour(b);
	}
}

void GameObject::removeBehaviour(Behaviour * behaviour)
{
	int index = indexOf(m_behaviours, behaviour);
	int willBeRemovedIndex = indexOf(m_behavioursToRemove, behaviour);
	if (index != -1 && willBeRemovedIndex == -1)
	{
		// So the behaviour is contained in the list of behaviours and not in the list of the behaviours that WILL be deleted
		if (m_isUpdating) {
			m_behavioursToRemove.push_back(behaviour);
		}
		else
		{
			doRemoveBehaviour(behaviour);
		}
		
	}
}

void GameObject::doAddBehaviour(Behaviour * behaviour)
{
	m_behaviours.push_back(behaviour);
}

void GameObject::doRemoveBehaviour(Behaviour * behaviour)
{
	// Remove from the vector and delete
	int index = indexOf(m_behaviours, behaviour);
	m_behaviours.erase(m_behaviours.begin() + index);
	delete behaviour;
}

void GameObject::setActive(bool activeState)
{
	m_isActive = activeState;
}

bool GameObject::isActive()
{
	return m_isActive;
}

GameObject * GameObject::createNew()
{
	GameObject* go = nullptr;
	if (SceneManager::hasActiveScene())
	{
		go = new GameObject();
		GameObjectsManager::addGameObject(go);
	}
	return go;
}

void GameObject::destroy(GameObject * gameObject)
{
	GameObjectsManager::destroyGameObject(gameObject);
}

