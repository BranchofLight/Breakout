// Class Objectives:
// - Handle all brick functionality

#pragma once

#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick(int, int, std::string);
	~Brick();

	void handleCollision();
	void handleBallCollision();

private:
};
