// Class Objectives:
// - Contain all code for handling ball objects

#pragma once;

#include "GameObject.h"
#include "Paddle.h"

class Ball : public GameObject
{
public:
	Ball(int, int, std::string);
	~Ball();

	void dropBall(float);
	bool getHasDropped();
	bool didHitBottom(int, int);

	void handleCollision();
	void handlePaddleCollision(Paddle*, int);
	void handleWallCollision(int, int);
	void handleAngleCollision(GameObject*);
	int getOverlapNormalAngle(int, int, LineSegment*, LineSegment*);

	void move(float);

private:
	bool hasDropped;

	sf::Sound bump;
	sf::SoundBuffer* buffer;
};
