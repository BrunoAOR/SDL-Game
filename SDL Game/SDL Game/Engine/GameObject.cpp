#include "GameObject.h"

#include "EngineUtils.cpp"
#include "Texture.h"
#include "Behaviour.h"
#include "RenderManager.h"
#include "SceneManager.h"


GameObject::GameObject()
{
	// Initialize texture empty
	texture = nullptr;
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


void GameObject::removeBehaviour(Behaviour * behaviour)
{
	int index = indexOf(m_behaviours, behaviour);
	if (index != -1)
	{
		// So the behaviour is contained in the list of behaviours
		// Remove from the vector and delete
		Behaviour * b = m_behaviours.at(index);
		m_behaviours.erase(m_behaviours.begin() + index);
		delete b;
	}
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
		if (!SceneManager::addGameObject(go))
		{
			delete go;
			go = nullptr;
		}
	}
	return go;
}

bool GameObject::destroy(GameObject * gameObject)
{
	// Success flag
	bool success = false;
	if (SceneManager::hasActiveScene())
	{
		if (SceneManager::removeGameObject(gameObject))
		{
			delete gameObject;
			success = true;
		}
	}
	return success;
}

