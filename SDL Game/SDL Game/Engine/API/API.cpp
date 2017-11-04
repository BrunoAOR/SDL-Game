#include "API.h"
#include "Engine/Engine.h"
#include "Engine/Scenes/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Time.h"


void ScenesAPI::loadScene(unsigned int index)
{
	engine->sceneManager->loadScene(index);
}


bool InputAPI::getKey(SDL_Scancode scancode)
{
	return engine->input->getKey(scancode);
}


bool InputAPI::getKeyUp(SDL_Scancode scancode)
{
	return engine->input->getKeyUp(scancode);
}


bool InputAPI::getKeyDown(SDL_Scancode scancode)
{
	return engine->input->getKeyDown(scancode);
}


Uint32 TimeAPI::time()
{
	return engine->time->time();
}


Uint32 TimeAPI::deltaTime()
{
	return engine->time->deltaTime();
}
