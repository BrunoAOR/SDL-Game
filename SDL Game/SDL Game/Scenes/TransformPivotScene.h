#pragma once

#include "Engine/Scenes/Scene.h"


class TransformPivotScene :
	public Scene
{
public:
	// Inherited via Scene
	virtual bool load() override;
	virtual void unload() override;
};

