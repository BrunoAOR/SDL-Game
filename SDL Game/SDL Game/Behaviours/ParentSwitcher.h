#pragma once

#include "Engine\Behaviour.h"
#include <memory>

class Transform;


class ParentSwitcher :
	public Behaviour
{
public:
	virtual void update() override;

	std::weak_ptr<Transform> parent1;
	std::weak_ptr<Transform> parent2;
};

