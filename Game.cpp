#include "stdafx.h"

Game::Game()
{
	bricks = new ResourceManager();
	paddle = NULL;
	ball = NULL;

	if (!music.openFromFile("music/tetris_music.ogg"))
	{
		// do nothing
	}	
}

Game::~Game()
{
	if (ball != NULL)
		delete ball;
	if (paddle != NULL)
		delete paddle;
	delete bricks;	
}

void Game::setup(int w, int h)
{
	window.create(sf::VideoMode(w, h), "Breakout", sf::Style::Close);
}

sf::RenderWindow* Game::getWindow()
{
	return &window;
}

// Only for testing purposes
void Game::generateLevel(int rows, float ballSpeed, bool isRandom) 
{
	this->ballSpeed = ballSpeed;

	// Don't set position till size is calculated
	paddle = new Paddle(0, 0, "images/paddle_texture.png");
	// Wait for Paddle's constructor to calculate size and then position it center bottom
	paddle->getSprite()->setPosition(((window.getSize().x - paddle->getSprite()->getTexture()->getSize().x) / 2), window.getSize().y - paddle->getSprite()->getTexture()->getSize().y);

	ball = new Ball(0, 0, "images/ball_texture.png");
	//ball->getSprite()->setPosition(((window.getSize().x - ball->getSprite()->getTexture()->getSize().x) / 2), window.getSize().y-200);
	ball->getSprite()->setPosition(((window.getSize().x - ball->getSprite()->getTexture()->getSize().x) / 2), window.getSize().y-300);

	/*rect.setSize(sf::Vector2f(ball->getSprite()->getTexture()->getSize().x, ball->getSprite()->getTexture()->getSize().y));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(5);
	rect.setFillColor(sf::Color::Transparent);*/

	bricks->add(new Brick(ball->getSprite()->getPosition().x-200, window.getSize().y-125, "images/brick_texture.png"));
	bricks->add(new Brick(ball->getSprite()->getPosition().x-49, window.getSize().y-125, "images/brick_texture.png"));
	bricks->add(new Brick(ball->getSprite()->getPosition().x-223, ball->getSprite()->getPosition().y+19, "images/brick_texture.png"));

	int y =50;
	for (int r = 0; r < rows; r++)
	{
		for (int x = 0; x < window.getSize().x; x += 50)
		{
			bricks->add(new Brick(x, y, "images/brick_texture.png"));			
		}

		// Next row level
		y += 50;
	}	

	backgroundTexture = sf::Texture();
	backgroundSprite = sf::Sprite();

	// Load background
	if (!backgroundTexture.loadFromFile("images/background_texture.png"))
	{
		backgroundTexture.create(800, 600);
	}
	
	backgroundSprite.setTexture(backgroundTexture);

	//music.play();
	//music.setLoop(true);
}

void Game::eventLoop(float elapsedTimeSeconds)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (paddle->getDirectionMoving() != LEFT)
			paddle->setSpeedX(0.0f);

		paddle->accelerate(elapsedTimeSeconds);
		paddle->move(LEFT, elapsedTimeSeconds);
		paddle->fixPosition(window.getSize().x, window.getSize().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (paddle->getDirectionMoving() != RIGHT)
			paddle->setSpeedX(0.0f);

		paddle->accelerate(elapsedTimeSeconds);
		paddle->move(RIGHT, elapsedTimeSeconds);
		paddle->fixPosition(window.getSize().x, window.getSize().y);
	}
	else
	{
		paddle->move(paddle->getDirectionMoving(), elapsedTimeSeconds);
		paddle->decelerate(elapsedTimeSeconds);
		paddle->fixPosition(window.getSize().x, window.getSize().y);
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && !ball->getHasDropped())
	{
		ball->dropBall(ballSpeed);
	}
}

void Game::logicLoop(float elapsedTimeSeconds)
{
	// Ball moves all the time unless outward forces cause it to be still (NONE)	
	//ball->move(ball->getHorizontal(), elapsedTimeSeconds);
	//ball->move(ball->getVertical(), elapsedTimeSeconds);
	ball->move(elapsedTimeSeconds);

	if (ball->isOffScreen(window.getSize().x, window.getSize().y))
	{
		if (ball->didHitBottom(window.getSize().x, window.getSize().y))
		{
			window.close();
		}
		ball->handleWallCollision(window.getSize().x, window.getSize().y);	
		
		// Stops the ball from getting stuck in the wall
		ball->move(elapsedTimeSeconds);
	}	

	if (ball->isCollision(paddle))
	{
		ball->handlePaddleCollision(paddle, ball->getSprite()->getPosition().x + ball->getSprite()->getTexture()->getSize().y);
	}

	for (int i = 0; i < bricks->getObjectAmount(); i++)
	{
		if (ball->isCollision(bricks->getObjectAt(i)))
		{
			ball->handleAngleCollision(bricks->getObjectAt(i));				
			// Removes brick
			bricks->dispose(i);
			// Does nothing right now - except crash
			//bricks->getObjectAt(i)->handleCollision();
			break;
		}
	}	
}

void Game::drawAll()
{
	window.draw(backgroundSprite);

	if (paddle != NULL)
		window.draw(*paddle->getSprite());
	if (ball != NULL)
	{
		//rect.setPosition(ball->getSprite()->getPosition().x, ball->getSprite()->getPosition().y);
		window.draw(*ball->getSprite());
		//window.draw(rect);
	}

	for (int i = 0; i < bricks->getObjectAmount(); i++)
		window.draw(*bricks->getObjectAt(i)->getSprite());
}

ResourceManager* Game::getResourceManager()
{
	return bricks;
}

Paddle* Game::getPaddle()
{
	return paddle;
}

Ball* Game::getBall()
{
	return ball;
}