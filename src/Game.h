// Class Objectives:
// Setup game
// Handle any changes in view (eg. menus, level advances, etc) including generating a new level
// Hold reference to a Level which holds all level objects
// Changes score as approriate
// Disposes of all objects when game is closed

#pragma once

#include "ResourceManager.h"
#include "SFML\Graphics.hpp"

class Game
{
public:
	Game();
	~Game();

	void setup(int, int);

	void generateLevel(int, float, bool);

	void eventLoop(float);
	void logicLoop(float);

	sf::RenderWindow* getWindow();
	ResourceManager*  getResourceManager();

	void drawAll();

	Paddle* getPaddle();
	Ball*   getBall();

private:
	// Exclusively used for bricks
	ResourceManager* bricks;

	// Window object for entire game run
	sf::RenderWindow window;

	// Individual objects which may be important to reference specifically
	// Note: They are still in the main list
	// Note: Normally, a key/data system (or similar) would be implemented but that is overengineering for this game
	Ball   *ball;
	Paddle *paddle;

	sf::Sprite  backgroundSprite;
	sf::Texture backgroundTexture;

	float ballSpeed;

	sf::Music music;

	//sf::RectangleShape rect;
};
