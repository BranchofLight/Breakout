#include "stdafx.h"

Brick::Brick(int x, int y, std::string filepath) : GameObject(x, y, filepath) 
{
}

Brick::~Brick()
{
}

void Brick::handleCollision()
{
	this->handleBallCollision();
}

void Brick::handleBallCollision()
{
	// do nothing
}
