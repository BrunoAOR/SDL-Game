#include "scenesConfig.h"

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

	success &= SceneManager::addScene<TestScene>();
	success &= SceneManager::addScene<TestScene2>();
	success &= SceneManager::addScene<TestScene3>();
	success &= SceneManager::addScene<TransformPivotScene>();
	success &= SceneManager::addScene<TimeTesterScene>();
	success &= SceneManager::addScene<CollidersScene>();
	success &= SceneManager::addScene<ParentSwitchScene>();
	success &= SceneManager::addScene<SpriteSheetScene>();
	SceneManager::loadScene(5);

	return success;
}
