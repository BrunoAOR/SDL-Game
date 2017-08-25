#pragma once


class Scene
{
public:
	virtual ~Scene();
	virtual bool load() = 0;
	virtual void unload() = 0;
};
