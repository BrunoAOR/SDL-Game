#pragma once

#include "Engine/Behaviour.h"

#include "Engine/Vector2.h"

class Pivotter :
	public Behaviour
{
public:
	// Inherited via Behaviour
	virtual void start() override;
	virtual void update() override;

	Vector2 positionPivot;
	Vector2 rotationPivot;
	Vector2 scalePivot;
	
	Vector2 position;
	double rotation;
	Vector2 scale;

private:
	double step;
	double rotStep;

	enum class MoveMode {
		POS,
		ROT,
		SCA
	};

	enum class Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	MoveMode mode;

	Vector2& getActivePivot();
	void movePivot(Vector2& pivot, const Direction& direction);
	void updateGO();
	void printPivotInfo();
	
};

