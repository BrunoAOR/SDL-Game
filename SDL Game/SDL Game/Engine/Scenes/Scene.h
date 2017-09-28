#pragma once


class Scene
{
	friend class SceneManager;
public:
	virtual ~Scene();
	virtual bool load() = 0;
	virtual void unload() = 0;
};
