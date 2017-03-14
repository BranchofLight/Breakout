#include "stdafx.h"

Paddle::Paddle(int x, int y, std::string filepath) : GameObject(x, y, filepath) 
{
	this->speedx = 0.0f;
	this->acc = 1600.0f;
	this->dec = 2000.0f;
	this->topSpeed = 1000.0f;
}

Paddle::~Paddle()
{
}

// Overloads the super move() so the last direciton moved can be saved
void Paddle::move(DIRECTION dir, float time)
{
	switch (dir)
	{
		case RIGHT:
			sprite->move(time * speedx, 0);
			break;
		case LEFT:
			sprite->move(time * -speedx, 0);
			break;
		default:
			break;
	}

	lastMoved = dir;
}

void Paddle::handleCollision()
{
	// do nothing
}

DIRECTION Paddle::getDirectionMoving()
{
	return lastMoved;
}
