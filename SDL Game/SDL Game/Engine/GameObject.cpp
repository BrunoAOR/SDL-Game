#include "GameObject.h"

#include "EngineUtils.cpp"
#include "Texture.h"
#include "Behaviour.h"
#include "RenderManager.h"


GameObject::GameObject()
{
	// Initialize texture empty
	texture = nullptr;
}


GameObject::~GameObject()
{
	removeTexture();
	for (Behaviour* b : behaviours) {
		removeBehaviour(b);
	}
}


bool GameObject::addTexture(std::string path)
{
	removeTexture();
	texture = RenderManager::createTexture(path);

	if (texture != nullptr) {
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


void GameObject::addBehaviour(Behaviour * behaviour)
{
	if (indexOf(behaviours, behaviour) == -1) {
		// So, the behaviour hasn't been previously added
		behaviours.push_back(behaviour);
	}
}


void GameObject::removeBehaviour(Behaviour * behaviour)
{
	int index = indexOf(behaviours, behaviour);
	if (index != -1) {
		// So the behaviour is contained in the list of behaviours
		// Remove from the vector and delete
		Behaviour * b = behaviours.at(index);
		behaviours.erase(behaviours.begin() + index);
		delete b;
	}
}
