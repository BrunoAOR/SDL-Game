#pragma once

#include "Engine\Behaviour.h"


class Mover :
	public Behaviour
{
public:
	Mover();
	// Inherited via Behaviour
	virtual void update() override;
	bool useWASD;
	double speed;

private:
	void moveWithArrows(double& x, double& y);
	void moveWithWASD(double& x, double& y);
};
