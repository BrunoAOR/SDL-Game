#include <SDL.h>
#include <SDL_image.h>

#include "constants.h"
#include "Input.h"
#include "GameObjectsManager.h"
#include "RenderManager.h"
#include "SceneManager.h"


// Global variables
SDL_Window* gWindow = nullptr;

// Function declarations
bool init();
bool setupScenes();
void loop();
void close();


int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize SDL!\n");
	}
	else
	{
		if (!setupScenes())
		{
			printf("Failed to load scene!\n");
		}
		else
		{
			loop();
		}
	}

	close();

	return 0;
}


bool init()
{
	// Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error: SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Error: Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create Renderer for window (used for texture rendering)
			if (RenderManager::createRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED))
			{
				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
				{
					printf("Error: SDL_Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

#include "../TestScene.h"
#include "../TestScene2.h"
#include "../TestScene3.h"
#include "../TransformPivotScene.h"

bool setupScenes()
{
	// Success flag
	bool success = true;

	success &= SceneManager::addScene<TestScene>();
	success &= SceneManager::addScene<TestScene2>();
	success &= SceneManager::addScene<TestScene3>();
	success &= SceneManager::addScene<TransformPivotScene>();
	SceneManager::loadScene(0);

	return success;
}


void handleEvents(bool& shouldQuit)
{
	// Event handler
	SDL_Event e;

	// Clear Input states
	Input::clearStates();

	while (SDL_PollEvent(&e))
	{
		// User requested quit
		if (e.type == SDL_QUIT)
		{
			shouldQuit = true;
		}
		else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			Input::setKeyDown(e.key.keysym.scancode);
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			Input::setKeyUp(e.key.keysym.scancode);
		}
	}
}


void loop()
{
	// Main loop flag
	bool quit = false;

	// While application is running
	while (!quit)
	{
		handleEvents(quit);

		SceneManager::refreshScenes();

		GameObjectsManager::updateGameObjectsAndBehaviours();
		
		RenderManager::update();
	}

}


void close()
{
	// Unload scene
	SceneManager::close();

	// Destroy window and its renderer
	RenderManager::close();
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
