#include "GameObject.h"

#include "EngineUtils.h"
#include "Texture.h"
#include "Behaviour.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "GameObjectsManager.h"


int GameObject::m_nextId = 0;

GameObject::GameObject()
{
	m_id = m_nextId++;
	printf("GO constructed: %i\n", m_id);
	// Initialize texture empty
	texture = nullptr;

	m_isActive = true;
}


GameObject::~GameObject()
{
	removeTexture();
	m_components.clear();
	m_behaviours.clear();
	printf("GO destructed: %i\n", m_id);
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
	for (auto c : m_componentsToAdd)
	{
		doAddComponent(c);
	}
	m_componentsToAdd.clear();

	for (auto c : m_componentsToRemove)
	{
		doRemoveComponent(c);
	}
	m_componentsToRemove.clear();
}

void GameObject::removeComponent(std::weak_ptr<Component> component)
{
	int componentIndex = indexOf(m_components, component.lock());
	int willBeRemovedIndex = indexOf(m_componentsToRemove, component);
	if (componentIndex != -1 && willBeRemovedIndex == -1)
	{
		// So the component is contained in the list of components and not in the list of the components that WILL be deleted
		m_componentsToRemove.push_back(component);
	}
}

void GameObject::doAddComponent(std::shared_ptr<Component> component)
{
	// No need to check for components's presence in m_components since this funciton gets called with newly instantiated components only
	m_components.push_back(component);
	if (std::shared_ptr<Behaviour> behaviour = std::dynamic_pointer_cast<Behaviour>(component))
	{
		m_behaviours.push_back(behaviour);
	}
}

void GameObject::doRemoveComponent(std::weak_ptr<Component> component)
{
	// Remove from the vector and delete
	int componentIndex = indexOf(m_components, component.lock());
	if (componentIndex != -1)
	{
		if (std::shared_ptr<Behaviour> behaviour = std::dynamic_pointer_cast<Behaviour>(component.lock()))
		{
			int behaviourIndex = indexOf(m_behaviours, behaviour);
			if (behaviourIndex != -1)
			{
				m_behaviours.erase(m_behaviours.begin() + behaviourIndex);
			}
		}
		m_components.erase(m_components.begin() + componentIndex);
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

std::weak_ptr<GameObject> GameObject::createNew()
{
	std::weak_ptr<GameObject> weakGo;
	if (SceneManager::hasActiveScene())
	{
		auto go = std::make_shared<GameObject>();
		go->self = go;
		GameObjectsManager::addGameObject(go);
		weakGo = go;
	}
	return weakGo;
}

void GameObject::destroy(std::weak_ptr<GameObject> gameObject)
{
	GameObjectsManager::destroyGameObject(gameObject);
}

