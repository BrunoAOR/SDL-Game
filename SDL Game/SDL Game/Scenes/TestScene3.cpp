#include "TestScene3.h"

#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/Transforms/Transform.h"

#include "Behaviours/GOKiller.h"
#include "Behaviours/SceneChanger.h"


bool TestScene3::load()
{
	// Success flag
	bool success = true;

	auto parentGO = GameObject::createNew().lock();
	parentGO->addComponent<SceneChanger>();

	auto child1 = GameObject::createNew().lock();
	child1->transform.lock()->setParent(parentGO->transform);
	
	auto child2 = GameObject::createNew().lock();
	child2->transform.lock()->setParent(parentGO->transform);

	auto child11 = GameObject::createNew().lock();
	child11->transform.lock()->setParent(child1->transform);

	auto child12 = GameObject::createNew().lock();
	child12->transform.lock()->setParent(child1->transform);
	
	auto child21 = GameObject::createNew().lock();
	child21->transform.lock()->setParent(child2->transform);

	//success = child1->transform.lock()->setParent(child21->transform);

	child1->addComponent<GOKiller>();
	printf("Scene loaded\n");
	return success;
}

void TestScene3::unload()
{
}
