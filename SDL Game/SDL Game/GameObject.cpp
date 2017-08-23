#include "GameObject.h"
#include "Crosshair.h"
#include "Texture.h"


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
	// Success flag
	bool success = true;

	removeTexture();
	texture = new Texture(m_renderer);
	if (!texture->loadFromFile(path))
	{
		printf("Error: Unable to add texture from path %s!", path.c_str());
		success = false;
	}
	return success;
}

void GameObject::removeTexture()
{
	if (texture != nullptr)
	{
		texture->free();
		delete texture;
		texture = nullptr;
	}
}
