// Class objectives:
// - Contain all functionality for the paddle

#pragma once

#include "GameObject.h"

class Paddle : public GameObject
{
public:
	Paddle(int, int, std::string);
	~Paddle();

	void handleCollision();

	void move(DIRECTION, float);

	DIRECTION getDirectionMoving();

private:
	DIRECTION lastMoved;
};
