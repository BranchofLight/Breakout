// Class Objectives:
// - Create a base class for all objects used

#pragma once;

#include "LineSegment.h"

enum DIRECTION { UP, DOWN, LEFT, RIGHT, NONE };

class GameObject
{
public:
	GameObject(int, int, std::string);
	~GameObject();

	void move(DIRECTION, float);
	void accelerate(float);
	void decelerate(float);
	
	bool isOffScreen(int, int);
	void fixPosition(int, int);

	sf::FloatRect getCollisionBox();

	bool isCollision(GameObject*);

	sf::Sprite* getSprite();

	void setSpeedX(float);
	void setSpeedY(float);

	int getAngle();
	void setAngle(int);
	
	// Generic collision handling
	virtual void handleCollision();

	LineSegment getTopLine();
	LineSegment getBottomLine();
	LineSegment getRightLine();
	LineSegment getLeftLine();

protected:
	sf::Texture texture;
	sf::Sprite* sprite;

	float speedx;
	float speedy;
	float topSpeed;
	float acc;	
	float dec;

	LineSegment* topLine;
	LineSegment* rightLine;
	LineSegment* bottomLine;
	LineSegment* leftLine;

	int angle;

	static const LineSegment origin;
};
