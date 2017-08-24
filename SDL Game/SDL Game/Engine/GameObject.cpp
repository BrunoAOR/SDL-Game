#include "GameObject.h"

#include "Texture.h"
#include "RenderManager.h"

GameObject::GameObject(SDL_Renderer* renderer)
{
	// Store renderer reference
	m_renderer = renderer;

	// Initialize texture empty
	texture = nullptr;
}

GameObject::~GameObject()
{
	removeTexture();
}

bool GameObject::addTexture(std::string path)
{
	removeTexture();
	texture = new Texture(m_renderer);
	if (!texture->loadFromFile(path))
	{
		printf("Error: Unable to add texture from path %s!", path.c_str());
		delete texture;
		texture = nullptr;
	}

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
