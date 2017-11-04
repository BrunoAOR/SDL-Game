#pragma once

class SceneManager;

class Engine
{
public:
	Engine();
	~Engine();

	bool init();
	void handleEvents(bool& shouldQuit);
	void loop();
	void close();

private:
	SceneManager* sceneManager;

	bool initSDL();
	bool initEngine();
};

