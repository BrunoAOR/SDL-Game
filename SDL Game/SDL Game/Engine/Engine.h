#pragma once

class Time;
class Input;
class SceneManager;
class GameObjectsManager;
class ComponentsManager;


class Engine
{
public:
	Engine();
	~Engine();

	bool init();
	void handleEvents(bool& shouldQuit);
	void loop();
	void close();

	Time* time = nullptr;
	Input* input = nullptr;
	SceneManager* sceneManager = nullptr;
	GameObjectsManager* gameObjectsManager = nullptr;
	ComponentsManager* componentsManager = nullptr;

private:
	bool initSDL();
	bool initEngine();
};

extern Engine* engine;
