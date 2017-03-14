#include "stdafx.h"

Ball::Ball(int x, int y, std::string filepath) : GameObject(x, y, filepath) 
{
	// Speed set on drop ball

	hasDropped = false;
	
	bump = sf::Sound();
	buffer = new sf::SoundBuffer();
	if (!buffer->loadFromFile("sounds/bump.wav"))
	{
		std::cout << "ERROR: Sound did not load.\n";
	}

	bump.setBuffer(*buffer);

	// For bottom left rect
	angle = 315;
	// For bottom middle rect
	//angle = 0;
	// For left rect
	//angle = 270;
}

Ball::~Ball()
{
	delete buffer;
}

void Ball::dropBall(float speed)
{
	this->speedy = speed;
	this->speedx = speed;
	std::cout << "speedx: " << speedx << "\n";
	std::cout << "speedy: " << speedy << "\n";
	hasDropped = true;
}

void Ball::handleWallCollision(int width, int height)
{
	bump.play();
	
	sf::FloatRect ballBox = getCollisionBox();
	float normalAngle;

	if (ballBox.left < 0 || ballBox.left + ballBox.width > width)
	{
		normalAngle = 90;
	}
	else if (ballBox.top < 0 || ballBox.top + ballBox.height > height)
	{
		normalAngle = 0;
	}

	std::cout << "Old Angle: " << angle << "\n";
	std::cout << "Normal: " << normalAngle << "\n";
	
	angle = normalizeAngle((normalAngle + (normalAngle - angle)) - 180);

	std::cout << "New Angle: " << angle << "\n";

	//fixPosition(width, height);

	/*
	if (ballBox.left < 0 || ballBox.left + ballBox.width > width)
		speedx = -speedx;
	else if (ballBox.top < 0 || ballBox.top + ballBox.height > height)
		speedy = -speedy;
		*/
}

bool Ball::didHitBottom(int width, int height)
{
	return false;
	//return sprite->getPosition().y + sprite->getTexture()->getSize().y > height;
}

void Ball::move(float time)
{
 	sprite->move(time * speedx * sin(angle * (PI/180)), 0);
	sprite->move(0, time * speedy * cos(angle * (PI/180)));
}

// Used for brick collision
void Ball::handleAngleCollision(GameObject* object)
{	
	bump.play();

	sf::FloatRect ballBox = getCollisionBox();
	sf::FloatRect objBox = object->getCollisionBox();
	std::cout << "--- NEW COLLISION ---\n";
	std::cout << "Old angle: " << angle << "\n";	
	std::cout << "Old Speed X: " << speedx << "\n";
	std::cout << "Old Speed Y: " << speedy << "\n";
	float normalAngle = -1;

	// Quads made up from the ball's collision box
	// All 4 are evenly sized
	sf::FloatRect topLeftQuad(ballBox.left, ballBox.top, ballBox.width / 2, ballBox.height / 2);
	sf::FloatRect topRightQuad(ballBox.left + ballBox.width / 2, ballBox.top, ballBox.width / 2, ballBox.height / 2);
	sf::FloatRect bottomLeftQuad(ballBox.left, ballBox.top + ballBox.height / 2, ballBox.width / 2, ballBox.height / 2);
	sf::FloatRect bottomRightQuad(ballBox.left + ballBox.width / 2, ballBox.top + ballBox.height / 2, ballBox.width / 2, ballBox.height / 2);
	
	if (topLeftQuad.intersects(objBox))
	{
		if (topRightQuad.intersects(objBox))
		{
			std::cout << "Bottom hit.\n";
			normalAngle = calculateAngle(object->getBottomLine().calculateNormal(), origin);	
		}
		// This else is repeated below when topLeftQuad is checked first again
		else
		{
			// Relevant changes (differs for each)
			int deltaX = ballBox.left - (objBox.left + objBox.width);
			int deltaY = ballBox.top - (objBox.top + objBox.height);

			std::cout << "Special hit top left.\n";
			normalAngle = this->getOverlapNormalAngle(deltaX, deltaY, &object->getRightLine(), &object->getBottomLine());
		}
	}
	else if (bottomLeftQuad.intersects(objBox))
	{
		if (bottomRightQuad.intersects(objBox))
		{
			std::cout << "Top hit.\n";
			normalAngle = calculateAngle(object->getTopLine().calculateNormal(), origin);
		}		
		else
		{
			int deltaX = ballBox.left - (objBox.left + objBox.width);
			int deltaY = (ballBox.top + ballBox.height) - objBox.top;

			std::cout << "Special hit bottom left.\n";
			normalAngle = this->getOverlapNormalAngle(deltaX, deltaY, &object->getRightLine(), &object->getTopLine());
		}
	}
	else if (topLeftQuad.intersects(objBox))
	{
		if (bottomLeftQuad.intersects(objBox))
		{
			std::cout << "Right hit.\n";
			normalAngle = calculateAngle(object->getRightLine().calculateNormal(), origin);
		}
		else
		{
			int deltaX = ballBox.left - (objBox.left + objBox.width);
			int deltaY = ballBox.top - (objBox.top + objBox.height);

			std::cout << "Special hit top left.\n";
			normalAngle = this->getOverlapNormalAngle(deltaX, deltaY, &object->getRightLine(), &object->getBottomLine());
		}
	}
	else if (topRightQuad.intersects(objBox))
	{
		if (bottomRightQuad.intersects(objBox))
		{
			std::cout << "Left hit.\n";
			normalAngle = calculateAngle(object->getLeftLine().calculateNormal(), origin);
		}
		else
		{
			int deltaX = (ballBox.left + ballBox.width) - objBox.left;
			int deltaY = ballBox.top - (objBox.top + objBox.height);

			std::cout << "Special hit top right.\n";
			normalAngle = this->getOverlapNormalAngle(deltaX, deltaY, &object->getLeftLine(), &object->getBottomLine());
		}
	}	
	// Must test bottom right alone as it's never tested alone above
	else if (bottomRightQuad.intersects(objBox))
	{
		int deltaX = (ballBox.left + ballBox.width) - objBox.left;
		int deltaY = (ballBox.top + ballBox.height) - objBox.top;

		std::cout << "Special hit bottom right.\n";
		normalAngle = this->getOverlapNormalAngle(deltaX, deltaY, &object->getLeftLine(), &object->getBottomLine());
	}

	// Final angle calculation
	angle = normalizeAngle((normalAngle + (normalAngle - angle)) - 180);

	std::cout << "Normal: " << normalAngle << "\n";
	std::cout << "New angle: " << angle << "\n";
	std::cout << "New Speed X: " << speedx << "\n";
	std::cout << "New Speed Y: " << speedy << "\n";
}

int Ball::getOverlapNormalAngle(int deltaX, int deltaY, LineSegment* lineX, LineSegment* lineY)
{
	// Convert to positive integer
	if (deltaX < 0)
		deltaX *= -1;
	if (deltaY < 0)
		deltaY *= -1;
			
	std::cout << "Delta Y: " << deltaY << "\n";
	std::cout << "Delta X: " << deltaX << "\n";
	
	if (deltaX > deltaY)
	{
		return calculateAngle(lineY->calculateNormal(), origin);
	}
	else if (deltaX < deltaY)
	{
		return calculateAngle(lineX->calculateNormal(), origin);
	}
	else
	{
		std::cout << "True corner hit.\n";
		// This will cause the angle calculation to rotate
		// the current angle by 180 degrees
		return angle;
	}
}

/*
// Used for brick collision
void Ball::handleAngleCollision(GameObject* object)
{	
	bump.play();

	sf::FloatRect ballBox = getCollisionBox();
	sf::FloatRect objBox = object->getCollisionBox();
	std::cout << "--- NEW COLLISION ---\n";
	std::cout << "Old angle: " << angle << "\n";	
	std::cout << "Old Speed X: " << speedx << "\n";
	std::cout << "Old Speed Y: " << speedy << "\n";
	float normalAngle;

	const int topLeftQuad = 0;
	const int topRightQuad = 0;
	const int bottomLeftQuad = 0;
	const int bottomRightQuad = 0;

	// If ball hit top
	// If bottom of ball is inside box and top is outside
	if (ballBox.top + ballBox.height > objBox.top && ballBox.top < objBox.top)
	{	
		std::cout << "Top hit.\n";
		normalAngle = calculateAngle(object->getTopLine().calculateNormal(), origin);	
	}
	// If ball hit the bottom
	// If top of the ball is inside box and bottom is outside
	else if (ballBox.top < objBox.top + objBox.height && ballBox.top + ballBox.height > objBox.top + objBox.height)
	{
		std::cout << "Bottom hit.\n";
		normalAngle = calculateAngle(object->getBottomLine().calculateNormal(), origin);
	}
	// If ball hit the right
	// If left of ball is inside box and right is outside
	else if (ballBox.left < objBox.left + objBox.width && ballBox.left + ballBox.width > objBox.left + objBox.width)
	{
		std::cout << "Right hit.\n";
		normalAngle = calculateAngle(object->getRightLine().calculateNormal(), origin);
	}
	// If ball hit the left
	// If right of box is inside box and left is outside
	else if (ballBox.left + ballBox.width > objBox.left && ballBox.left < objBox.left)
	{
		std::cout << "Left hit.\n";
		normalAngle = calculateAngle(object->getLeftLine().calculateNormal(), origin);
	}

	angle = normalizeAngle((normalAngle + (normalAngle - angle)) - 180);

	std::cout << "Normal: " << normalAngle << "\n";
	std::cout << "New angle: " << angle << "\n";
	std::cout << "New Speed X: " << speedx << "\n";
	std::cout << "New Speed Y: " << speedy << "\n";
}*/

void Ball::handlePaddleCollision(Paddle* paddle, int hitPointX)
{
	bump.play();

	// Somewhat arbitrary angle choices
	const int maxAngle = 240;
	const int minAngle = 120;

	const int width = paddle->getSprite()->getTexture()->getSize().x;

	// Because the paddle is seen as 0, width the 
	// hit point must be brought back to a point between
	// 0 and width
	hitPointX -= paddle->getSprite()->getPosition().x;

	std::cout << "Paddle collision\n";
	std::cout << "Old angle: " << angle << "\n";
	std::cout << "Width: " << width << "\n";
	std::cout << "hitPointX: " << hitPointX << "\n";
	// hitPointX acts as a percentage of the total angle (min/max) to use for new angle
	// The further right the hit point is the closer to max angle it is and the further left, closer to min angle
	angle = normalizeAngle((maxAngle - minAngle) * ((width - hitPointX) * 0.01) + minAngle);
	std::cout << "New angle: " << angle << "\n";
}

void Ball::handleCollision()
{
	// do nothing
}

bool Ball::getHasDropped()
{
	return hasDropped;
}