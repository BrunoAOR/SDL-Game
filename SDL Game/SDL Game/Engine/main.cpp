#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "BehavioursManager.h"
#include "RenderManager.h"
#include "constants.h"
#include "Input.h"
#include "GameObject.h"
#include "Texture.h"

#include "../Crosshair.h"
#include "../Crosshair2.h"

// Global variables
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
GameObject* crosshairGO = nullptr;
GameObject* crosshair2GO = nullptr;
GameObject* targetGO = nullptr;

// Function declarations
bool init();
bool loadScene();
void loop();
void unloadScene();
void close();

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize SDL!\n");
	}
	else
	{
		if (!loadScene())
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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				printf("Error: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
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

void render()
{
	// Set Render Color to white
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	
	// Clear screen
	SDL_RenderClear(gRenderer);

	// Render Texture to screen
	
	RenderManager::update();
	
	// Update screen
	SDL_RenderPresent(gRenderer);
}

void loop()
{
	// Main loop flag
	bool quit = false;

	// While application is running
	while (!quit)
	{
		handleEvents(quit);

		//crosshairGO->behaviour->update();
		BehavioursManager::update();
		
		render();
	}

}



void close()
{
	// Unload scene
	unloadScene();

	// Destroy window and its renderer
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = nullptr;
	gWindow = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool loadScene()
{
	// Loading success flag
	bool success = true;

	// Load gameobjects

	// Crosshair1
	crosshairGO = new GameObject(gRenderer);
	crosshairGO->transform.position = { 200, 200 };
	crosshairGO->behaviour = new Crosshair(crosshairGO);
	if (!crosshairGO->addTexture("assets/Crosshair.png"))
	{
		printf("Error: Failed to load crosshair texture image!\n");
		success = false;
	}
	else
	{
		crosshairGO->texture->setColor(0, 255, 255);
	}

	// Crosshair2
	crosshair2GO = new GameObject(gRenderer);
	crosshair2GO->transform.position = { constants::SCREEN_WIDTH - 200, 200 };
	crosshair2GO->behaviour = new Crosshair2(crosshair2GO);
	if (!crosshair2GO->addTexture("assets/Crosshair.png"))
	{
		printf("Error: Failed to load crosshair texture image!\n");
		success = false;
	}
	else
	{
		crosshair2GO->texture->setColor(255, 0, 255);
	}

	return success;
}

void unloadScene()
{
	// Free loaded GameObjects
	delete crosshairGO;
	crosshairGO = nullptr;
	delete crosshair2GO;
	crosshair2GO = nullptr;
}