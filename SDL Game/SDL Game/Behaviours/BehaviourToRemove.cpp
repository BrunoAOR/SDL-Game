#include "BehaviourToRemove.h"

#include <stdio.h>


BehaviourToRemove::~BehaviourToRemove()
{
	printf("BTR DESTROYED!\n");
}

void BehaviourToRemove::start()
{
	printf("BTR STARTED!\n");
}

void BehaviourToRemove::update()
{
	//printf("BTR UPDATED! ");
}
