#include "stdafx.h"

// Origin used for bounce calculations
const LineSegment GameObject::origin(0, 0, 0, 1);

GameObject::GameObject(int x, int y, std::string filepath) 
{
	sprite = new sf::Sprite();

	if (!texture.loadFromFile(filepath))
	{
		// These dimensions are from the desired size of the texture
		texture.create(100, 20);
	}
	else
	{
		texture.setSmooth(true);
	}

	sprite->setTexture(texture);	
	sprite->setPosition(x, y);

	//std::cout << "rect:\ntop: " << rect.top << ", left: " << rect.left << ", width: " << rect.width << ", height: " << rect.height << std::endl;

	// Default to innanimate
	speedx = 0.0f;
	speedy = 0.0f;
	acc = 0.0f;
	dec = 0.0f;
	topSpeed = 0.0f;	

	// Default should be parallel to the origin
	angle = 0;

	// To ease reading set a few variables for temp use
	int h = sprite->getTexture()->getSize().y;
	int w = sprite->getTexture()->getSize().x;

	leftLine = new LineSegment(x, y, x, y+h);
    rightLine = new LineSegment(x+w, y, x+w, y+h);
    topLine = new LineSegment(x, y, x+w, y);
    bottomLine = new LineSegment(x, y+h, x+w, y+h);

	/*std::cout << "--- NEW GAME OBJECT ---\n";
	std::cout << "Right box: " << calculateAngle(getRightLine(), origin) << std::endl;
	std::cout << "Left box: " << calculateAngle(getLeftLine(), origin) << std::endl;
	std::cout << "Top box: " << calculateAngle(getTopLine(), origin) << std::endl;
	std::cout << "Bottom box: " << calculateAngle(getBottomLine(), origin) << std::endl;
	std::cout << "--------- END ---------\n";

	if (calculateAngle(getRightLine(), origin) != 0 && calculateAngle(getRightLine(), origin) != 90
		|| calculateAngle(getLeftLine(), origin) != 0 && calculateAngle(getLeftLine(), origin) != 90
		|| calculateAngle(getTopLine(), origin) != 0 && calculateAngle(getTopLine(), origin) != 90
		|| calculateAngle(getBottomLine(), origin) != 0 && calculateAngle(getBottomLine(), origin) != 90)
	{
		std::cout << "ERROR: see above.\n";
	}*/
}

GameObject::~GameObject()
{
	delete sprite;

	delete leftLine;
	delete rightLine;
	delete topLine;
	delete bottomLine;
}

void GameObject::move(DIRECTION dir, float time)
{
	switch (dir)
	{
		case UP:
			sprite->move(0, time * -speedy);
			break;
		case DOWN:
			sprite->move(0, time * speedy);
			break;
		case RIGHT:
			sprite->move(time * speedx, 0);
			break;
		case LEFT:
			sprite->move(time * -speedx, 0);
			break;
		default:
			break;
	}
}

void GameObject::accelerate(float time)
{
	if (speedx < topSpeed)
	{
		speedx += time * acc;
	}

	//std::cout << "Speed: " << speed << "\n";
}

void GameObject::decelerate(float time)
{
	if (speedx > 0)
	{
		speedx -= time * dec;
	}
	
	if (speedx < 0)
	{
		speedx = 0;
	}

	//std::cout << "Speed: " << speed << "\n";
}

void GameObject::setSpeedX(float spd)
{
	this->speedx = spd;
}

void GameObject::setSpeedY(float spd)
{
	this->speedy = spd;
}

// Determines if object is off screen
bool GameObject::isOffScreen(int width, int height)
{
	if (sprite->getPosition().x + sprite->getTexture()->getSize().x > width)
		return true;
	else if (sprite->getPosition().x < 0)
		return true;

	if (sprite->getPosition().y < 0)
		return true;
	else if (sprite->getPosition().y + sprite->getTexture()->getSize().y > height)
		return true;

	return false;
}

// Takes screen width and height to determine if object is off screen
// Note: may not be useful for every object - use at own discretion
void GameObject::fixPosition(int width, int height)
{
	if (sprite->getPosition().x + sprite->getTexture()->getSize().x > width)
		sprite->setPosition(width - sprite->getTexture()->getSize().x, sprite->getPosition().y);
	else if (sprite->getPosition().x < 0)
		sprite->setPosition(0, sprite->getPosition().y);

	if (sprite->getPosition().y < 0)
		sprite->setPosition(sprite->getPosition().x, 0);
	else if (sprite->getPosition().y + sprite->getTexture()->getSize().y > height)
		sprite->setPosition(sprite->getPosition().x, height - sprite->getTexture()->getSize().y);
}

// Not only gets collision box but updates collision box
sf::FloatRect GameObject::getCollisionBox()
{
	return sprite->getGlobalBounds();
}

// Rectangle collision checking on another object with this
bool GameObject::isCollision(GameObject* that)
{
	return sprite->getGlobalBounds().intersects(that->getCollisionBox()); 
}

void GameObject::handleCollision()
{
}

void GameObject::setAngle(int ang)
{
	angle = ang;
}

int GameObject::getAngle()
{	
	return angle;
}

sf::Sprite* GameObject::getSprite()
{
	return sprite;
}

LineSegment GameObject::getTopLine()
{
	return *topLine;
}

LineSegment  GameObject::getBottomLine()
{
	return *bottomLine;
}

LineSegment GameObject::getLeftLine()
{
	return *leftLine;
}

LineSegment GameObject::getRightLine()
{
	return *rightLine;
}