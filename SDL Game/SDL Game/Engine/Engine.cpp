#include "Engine.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Engine/constants.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "Engine/Scenes/SceneManager.h"
#include "Engine/GameObjects/GameObjectsManager.h"
#include "Engine/Components/ComponentsManager.h"
#include "Engine/config/scenesConfig.h"

Engine::Engine()
{
}


Engine::~Engine()
{
}


bool Engine::init()
{
	// Initialization flag
	bool success = true;

	success &= initSDL();

	if (success)
	{
		success &= initEngine();
	}
	return success;
}


void Engine::handleEvents(bool& shouldQuit)
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


void Engine::loop()
{
	// Main loop flag
	bool quit = false;

	// While application is running
	while (!quit)
	{
		Time::updateTime();

		handleEvents(quit);

		SceneManager::refreshScenes();

		GameObjectsManager::update();

		ComponentsManager::update();
	}
}


void Engine::close()
{
	// Delete all ComponentManagers
	ComponentsManager::close();

	// Unload scene
	SceneManager::close();

	// Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


bool Engine::initSDL()
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
		// Initialize PNG loading
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
		{
			printf("Error: SDL_Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}

		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
	}
	return success;
}


bool Engine::initEngine()
{
	// Initialization flag
	bool success = true;

	if (!scenesConfig())
	{
		printf("Failed to setup scenes!\n");
		success = false;
	}
	else
	{
		// Initialize the ComponentsManager
		success &= ComponentsManager::init();
	}

	return success;
}
