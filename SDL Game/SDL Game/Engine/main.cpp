#include <SDL.h>
#include <SDL_image.h>

#include "Engine/constants.h"
#include "Engine/Input.h"
#include "Engine/GameObjects/GameObjectsManager.h"
#include "Engine/Scenes/SceneManager.h"
#include "Engine/Time.h"
#include "Engine/Components/ComponentsManager.h"
#include "Engine/Components/Behaviours/BehavioursManager.h"


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
		// Initialize PNG loading
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
		{
			printf("Error: SDL_Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}
		// Initialize the ComponentsManager
		success &= ComponentsManager::init();

	}
	return success;
}

#include "Scenes/TestScene.h"
#include "Scenes/TestScene2.h"
#include "Scenes/TestScene3.h"
#include "Scenes/TransformPivotScene.h"
#include "Scenes/TimeTesterScene.h"
#include "Scenes/CollidersScene.h"
#include "Scenes/ParentSwitchScene.h"
#include "Scenes/SpriteSheetScene.h"

bool setupScenes()
{
	// Success flag
	bool success = true;

	success &= SceneManager::addScene<TestScene>();
	success &= SceneManager::addScene<TestScene2>();
	success &= SceneManager::addScene<TestScene3>();
	success &= SceneManager::addScene<TransformPivotScene>();
	success &= SceneManager::addScene<TimeTesterScene>();
	success &= SceneManager::addScene<CollidersScene>();
	success &= SceneManager::addScene<ParentSwitchScene>();
	success &= SceneManager::addScene<SpriteSheetScene>();
	SceneManager::loadScene(7);

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
		Time::updateTime();

		handleEvents(quit);

		SceneManager::refreshScenes();

		GameObjectsManager::update();

		ComponentsManager::update();
	}
}


void close()
{
	// Delete all ComponentManagers
	ComponentsManager::close();

	// Unload scene
	SceneManager::close();

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
