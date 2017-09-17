#include "Mover.h"

#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "Engine/Vector2.h"

Mover::Mover()
{
	useWASD = false;
	speed = 100;
	speedStep = 50;
}


void Mover::update()
{
	Vector2 motion(0, 0);
	
	// Check speed
	if (Input::getKeyDown(SDL_SCANCODE_KP_PLUS))
	{
		speed += speedStep;
		printf("Speed: %i\n", speed);
	}
	if (Input::getKeyDown(SDL_SCANCODE_KP_MINUS))
	{
		speed -= speedStep;
		printf("Speed: %i\n", speed);
	}

	// Check motion
	if (useWASD)
	{
		moveWithWASD(motion.x, motion.y);
	}
	else
	{
		moveWithArrows(motion.x, motion.y);
	}
	
	if (motion.x != 0 || motion.y != 0)
	{
		if (motion.x != 0 && motion.y != 0) {
			double sqrt2 = sqrt(2);
			motion.x /= sqrt2;
			motion.y /= sqrt2;
		}

		double elapsedSeconds = Time::deltaTime() / 1000.0;
		motion.x *= speed * elapsedSeconds;
		motion.y *= speed * elapsedSeconds;

		Vector2 currentPos = gameObject()->transform.getLocalPosition();
		Vector2 targetPos = currentPos + motion;
		gameObject()->transform.setLocalPosition(targetPos);
	}
}

void Mover::moveWithArrows(double& x, double& y)
{
	x = 0;
	y = 0;
	if (Input::getKey(SDL_SCANCODE_UP))
	{
		y = +1;
	}
	if (Input::getKey(SDL_SCANCODE_DOWN))
	{
		y = -1;
	}
	if (Input::getKey(SDL_SCANCODE_LEFT))
	{
		x = -1;
	}
	if (Input::getKey(SDL_SCANCODE_RIGHT))
	{
		x = +1;
	}
}

void Mover::moveWithWASD(double& x, double& y)
{
	x = 0;
	y = 0;
	if (Input::getKey(SDL_SCANCODE_W))
	{
		y = +1;
	}
	if (Input::getKey(SDL_SCANCODE_S))
	{
		y = -1;
	}
	if (Input::getKey(SDL_SCANCODE_A))
	{
		x = -1;
	}
	if (Input::getKey(SDL_SCANCODE_D))
	{
		x = +1;
	}
}


