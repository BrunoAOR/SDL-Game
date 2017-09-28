#pragma once

#include <vector>
#include <memory>

class Component;


class ComponentManager
{
public:
	ComponentManager();
	virtual ~ComponentManager();

	bool subscribeComponent(std::weak_ptr<Component> component);
	bool unsubscribeComponent(std::weak_ptr<Component> component);
	
	virtual bool canManage(std::weak_ptr<Component> component) = 0;
	virtual void update() = 0;
	virtual bool init() = 0;
	virtual void close() = 0;
	virtual bool initializeComponent(std::weak_ptr<Component> component) = 0;

protected:
	
	std::vector<std::weak_ptr<Component>> m_components;
	std::vector<std::weak_ptr<Component>> m_componentsToSubscribe;
	std::vector<std::weak_ptr<Component>> m_componentsToUnsubscribe;

	void refreshComponents();
	void doSubscribe(std::weak_ptr<Component> component);
	void doUnsubscribe(std::weak_ptr<Component> component);
};
