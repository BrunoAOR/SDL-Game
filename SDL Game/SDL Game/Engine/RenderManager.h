#pragma once

#include <vector>
#include <string>
#include <SDL.h>

class GameObject;
class Texture;

class RenderManager
{
public:
	static void update();
	static void subscribeGameObject(GameObject* gameObject);
	static void unsubscribeGameObject(GameObject* gameObject);
	static bool createRenderer(SDL_Window* window, int index, Uint32 flags);
	static Texture* createTexture(std::string imagePath);
	static void close();
private:
	RenderManager();
	static SDL_Renderer* m_renderer;
	static std::vector<GameObject *> m_gameObjects;
};

