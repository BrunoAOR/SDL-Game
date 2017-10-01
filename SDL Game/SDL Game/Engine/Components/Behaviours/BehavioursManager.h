#pragma once

#include "Engine/Components/ComponentManager.h"

class Component;


class BehavioursManager final :
	public ComponentManager
{
	friend class ComponentsManager;
public:
	~BehavioursManager();

private:
	BehavioursManager();

	// Inherited via ComponentManager
	virtual ComponentType managedComponentType() override;
	virtual void update() override;
	virtual bool init() override;
	virtual void close() override;
	virtual bool initializeComponent(std::weak_ptr<Component> component) override;
};
