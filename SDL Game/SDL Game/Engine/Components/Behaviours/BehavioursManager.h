#pragma once

#include "Engine/Components/ComponentManager.h"

class Component;


class BehavioursManager final :
	public ComponentManager
{
	friend class ComponentsManager;
public:
	~BehavioursManager();

	// Inherited via ComponentManager
	virtual bool canManage(std::weak_ptr<Component> component) override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(std::weak_ptr<Component> component) override;

private:
	BehavioursManager();	
};
