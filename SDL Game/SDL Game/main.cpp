#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "constants.h"
#include "Input.h"
#include "GameObject.h"
#include "Texture.h"
#include "Crosshair.h"

// Global variables
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
GameObject* crosshairGO = nullptr;
GameObject* targetGO = nullptr;
Texture* crosshairTexture = nullptr;
Texture* targetTexture = nullptr;

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
	
	crosshairGO->texture->render((int)crosshairGO->transform.position.x,(int)crosshairGO->transform.position.y);

	int clipWidth = targetTexture->getWidth() / 2;
	int clipHeight = targetTexture->getHeight() / 2;
	SDL_Rect targetClips[4];

	targetClips[0] = { 0, 0, clipWidth, clipHeight };
	targetClips[1] = { clipWidth, 0, clipWidth, clipHeight };
	targetClips[2] = { 0, clipHeight, clipWidth, clipHeight };
	targetClips[3] = { clipWidth, clipHeight, clipWidth, clipHeight };
	
	int screenWidth = constants::SCREEN_WIDTH;
	int screenHeight = constants::SCREEN_HEIGHT;
	targetTexture->render(0, 0, &targetClips[0]);
	targetTexture->render(screenWidth - clipWidth, 0, &targetClips[1]);
	targetTexture->render(0, screenHeight - clipHeight, &targetClips[2]);
	targetTexture->render(screenWidth - clipWidth, screenHeight - clipHeight, &targetClips[3]);


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
		crosshairGO->behaviour->update();
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

	targetTexture = new Texture(gRenderer);
	if (!targetTexture->loadFromFile("assets/Target.png"))
	{
		printf("Error: Failed to load target texture image!\n");
		success = false;
	}
	return success;
}

void unloadScene()
{
	// Free loaded GameObjects
	delete crosshairGO;
	crosshairGO = nullptr;

	// Free loaded texture	
	targetTexture->free();
	delete targetTexture;
	targetTexture = nullptr;
}