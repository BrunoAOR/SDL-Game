#include <stdio.h>
#include "Engine.h"


int main(int argc, char* args[])
{
	Engine* engine = new Engine();

	if (!engine->init())
	{
		printf("Failed to initialize Engine!\n");
	}
	else
	{	
		engine->loop();
	}

	engine->close();
	delete engine;
	engine = nullptr;

 	return 0;
}
