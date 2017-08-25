#include "RenderManager.h"

#include "EngineUtils.cpp"
#include "GameObject.h"
#include "Texture.h"


SDL_Renderer* RenderManager::m_renderer = nullptr;
std::vector<GameObject *> RenderManager::m_gameObjects;


RenderManager::RenderManager()
{

}


void RenderManager::update()
{
	// Set Render Color to white
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xFF);

	// Clear screen
	SDL_RenderClear(m_renderer);

	for (GameObject* go : m_gameObjects)
	{
		go->texture->render((int)go->transform.position.x, (int)go->transform.position.y);
	}

	// Update screen
	SDL_RenderPresent(m_renderer);
}


void RenderManager::subscribeGameObject(GameObject * gameObject)
{
	if (indexOf(m_gameObjects, gameObject) == -1) {
		// So the gameObject hasn't previously been added
		m_gameObjects.push_back(gameObject);
	}
}


void RenderManager::unsubscribeGameObject(GameObject * gameObject)
{
	int index = indexOf(m_gameObjects, gameObject);
	if (index != -1) {
		// So, the behaviour is in the behaviours vector
		m_gameObjects.erase(m_gameObjects.begin() + index);
	}
}


bool RenderManager::createRenderer(SDL_Window * window, int index, Uint32 flags)
{
	// Success flag
	bool success = true;
	m_renderer = SDL_CreateRenderer(window, index, flags);
	if (m_renderer == nullptr)
	{
		printf("Error: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}


Texture * RenderManager::createTexture(std::string imagePath)
{
	if (m_renderer == nullptr) {
		printf("Error: No renderer has been created!");
		return nullptr;
	}

	Texture* texture = new Texture(m_renderer);
	if (!texture->loadFromFile(imagePath))
	{
		printf("Error: Unable to add texture from path %s!", imagePath.c_str());
		delete texture;
		texture = nullptr;
	}

	return texture;
}


void RenderManager::close()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}