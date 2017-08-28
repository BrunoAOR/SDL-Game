#include "GameObject.h"

#include "EngineUtils.h"
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
}


GameObject::~GameObject()
{
	removeTexture();
	for (Component* c : m_components)
	{
		delete c;
	}
	m_components.clear();
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


void GameObject::refreshComponents()
{
	for (Component* c : m_componentsToAdd)
	{
		doAddComponent(c);
	}
	m_componentsToAdd.clear();

	for (Component* c : m_componentsToRemove)
	{
		doRemoveComponent(c);
	}
	m_componentsToRemove.clear();
}

void GameObject::removeComponent(Component * component)
{
	int componentIndex = indexOf(m_components, component);
	int willBeRemovedIndex = indexOf(m_componentsToRemove, component);
	if (componentIndex != -1 && willBeRemovedIndex == -1)
	{
		// So the component is contained in the list of components and not in the list of the components that WILL be deleted
		m_componentsToRemove.push_back(component);
	}
}

void GameObject::doAddComponent(Component * component)
{
	m_components.push_back(component);
	if (Behaviour* behaviour = dynamic_cast<Behaviour*>(component))
	{
		m_behaviours.push_back(behaviour);
	}
}

void GameObject::doRemoveComponent(Component * component)
{
	// Remove from the vector and delete
	int componentIndex = indexOf(m_components, component);
	if (componentIndex != -1)
	{
		m_components.erase(m_components.begin() + componentIndex);
		if (Behaviour* behaviour = dynamic_cast<Behaviour*>(component))
		{
			int behaviourIndex = indexOf(m_behaviours, behaviour);
			if (behaviourIndex != -1)
			{
				m_behaviours.erase(m_behaviours.begin() + behaviourIndex);
			}
		}
		delete component;
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
		GameObjectsManager::addGameObject(go);
	}
	return go;
}

void GameObject::destroy(GameObject * gameObject)
{
	GameObjectsManager::destroyGameObject(gameObject);
}

