#pragma once

#include "Engine/ComponentManager.h"

class Component;


class BehavioursManager final :
	public ComponentManager
{
	friend class ComponentsManager;
public:
	~BehavioursManager();


	// Inherited via ComponentManager
	virtual void update() override;
	virtual bool canManage(std::weak_ptr<Component> component) override;

private:
	BehavioursManager();	
};

