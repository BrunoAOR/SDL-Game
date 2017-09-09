#include "TestScene3.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Behaviours/GOKiller.h"
#include "Behaviours/SceneChanger.h"


bool TestScene3::load()
{
	// Success flag
	bool success = true;

	auto parentGO = GameObject::createNew();
	parentGO.lock()->addComponent<GOKiller>();
	parentGO.lock()->addComponent<SceneChanger>();

	auto child1 = GameObject::createNew();
	child1.lock()->setParent(parentGO);
	
	auto child2 = GameObject::createNew();
	child2.lock()->setParent(parentGO);

	auto child11 = GameObject::createNew();
	child11.lock()->setParent(child1);

	auto child12 = GameObject::createNew();
	child12.lock()->setParent(child1);
	
	auto child21 = GameObject::createNew();
	child21.lock()->setParent(child2);

	success = child1.lock()->setParent(child21);
	auto GO = parentGO.lock();

	return success;
}

void TestScene3::unload()
{
}
