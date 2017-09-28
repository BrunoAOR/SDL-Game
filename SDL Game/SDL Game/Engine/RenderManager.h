#pragma once

#include <memory>
#include <vector>
#include <string>
#include <SDL.h>

class GameObject;
class Texture;


class RenderManager
{
public:
	static void update();
	static void subscribeGameObject(std::weak_ptr<GameObject> gameObject);
	static void unsubscribeGameObject(std::weak_ptr<GameObject> gameObject);
	static bool createRenderer(SDL_Window* window, int index, Uint32 flags);
	static Texture* createTexture(std::string imagePath);
	static void close();
private:
	RenderManager();
	static SDL_Renderer* m_renderer;
	static std::vector<std::weak_ptr<GameObject>> m_gameObjects;
};
