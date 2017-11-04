#include "scenesConfig.h"

#include "Engine/Engine.h"
#include "Engine/Scenes/SceneManager.h"
#include "Scenes/TestScene.h"
#include "Scenes/TestScene2.h"
#include "Scenes/TestScene3.h"
#include "Scenes/TransformPivotScene.h"
#include "Scenes/TimeTesterScene.h"
#include "Scenes/CollidersScene.h"
#include "Scenes/ParentSwitchScene.h"
#include "Scenes/SpriteSheetScene.h"


bool scenesConfig()
{
	// Success flag
	bool success = true;

	success &= engine->sceneManager->addScene<TestScene>();
	success &= engine->sceneManager->addScene<TestScene2>();
	success &= engine->sceneManager->addScene<TestScene3>();
	success &= engine->sceneManager->addScene<TransformPivotScene>();
	success &= engine->sceneManager->addScene<TimeTesterScene>();
	success &= engine->sceneManager->addScene<CollidersScene>();
	success &= engine->sceneManager->addScene<ParentSwitchScene>();
	success &= engine->sceneManager->addScene<SpriteSheetScene>();
	engine->sceneManager->loadScene(5);

	return success;
}
