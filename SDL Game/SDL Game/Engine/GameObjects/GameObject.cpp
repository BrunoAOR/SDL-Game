#include "GameObject.h"

#include "Engine/Engine.h"
#include "Engine/EngineUtils.h"
#include "Engine/Components/Transforms/Transform.h"
#include "Engine/Scenes/SceneManager.h"
#include "Engine/GameObjects/GameObjectsManager.h"


// TESTING START
int GameObject::s_alive = 0;
int GameObject::s_nextId = 0;
// TESTING END


GameObject::GameObject()
{
	// TESTING START
	m_id = s_nextId++;
	printf("GO constructed -id: %i  ||  Alive: %i\n", m_id, ++s_alive);
	// TESTING END

	m_isActive = true;
}


GameObject::~GameObject()
{
	m_components.clear();

	// TESTING START
	printf("GO  destructed -id: %i  ||  Alive: %i\n", m_id, --s_alive);
	// TESTING END
}


void GameObject::refreshComponents()
{
	// Remove components
	for (auto c : m_componentsToRemove)
	{
		doRemoveComponent(c);
	}
	m_componentsToRemove.clear();

	// Add new components
	for (auto c : m_componentsToAdd)
	{
		doAddComponent(c);
	}
	m_componentsToAdd.clear();
}


void GameObject::removeComponent(std::weak_ptr<Component> component)
{
	int componentIndex = EngineUtils::indexOf(m_components, component.lock());
	int willBeRemovedIndex = EngineUtils::indexOf(m_componentsToRemove, component);
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
}


void GameObject::doRemoveComponent(std::weak_ptr<Component> component)
{
	// Remove from the vector and delete
	int componentIndex = EngineUtils::indexOf(m_components, component.lock());
	if (componentIndex != -1)
	{
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
	if (engine->sceneManager->hasActiveScene())
	{
		auto go = std::make_shared<GameObject>();
		engine->gameObjectsManager->addGameObject(go);
		go->m_self = go;
		// Add and setup transform
		go->transform = go->addComponent<Transform>();
		weakGo = go;
	}
	return weakGo;
}


void GameObject::destroy(std::weak_ptr<GameObject> gameObject)
{
	engine->gameObjectsManager->destroyGameObject(gameObject);
}
