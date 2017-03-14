// Breakout.cpp : Defines the entry point for the console application.
#include "stdafx.h"
// For memory leak detection
//#include "vld.h"

void renderLoop(Game*);
void writeNormal(LineSegment);

int main()
{
    Game game;
	game.setup(800, 600);

	/*Ball ball(5, 20, "images/ball_texture.png");
	Brick box(0, 0, "images/brick_texture.png");
	LineSegment origin(0, 0, 0, 1);

	std::cout << "Right box "; writeNormal(box.getRightLine().calculateNormal()); std::cout << ": " << calculateAngle(box.getRightLine(), origin) << std::endl;
	std::cout << "Left box "; writeNormal(box.getLeftLine().calculateNormal()); std::cout << ": " << calculateAngle(box.getLeftLine(), origin) << std::endl;
	std::cout << "Top box "; writeNormal(box.getTopLine().calculateNormal()); std::cout << ": " << calculateAngle(box.getTopLine(), origin) << std::endl;
	std::cout << "Bottom box "; writeNormal(box.getBottomLine().calculateNormal()); std::cout << ": " << calculateAngle(box.getBottomLine(), origin) << std::endl;

	std::cout << "Angle (top ball / origin): " << calculateAngle(ball.getTopLine(), origin) << "\n";
	std::cout << "Simulating a bounce on the right side of box...\n";	
	std::cout << "Old Angle: " << ball.getAngle() << "\n";
	int normalAngle = calculateAngle(box.getRightLine().calculateNormal(), origin);
	int newAngle = normalizeAngle(normalAngle + (normalAngle - ball.getAngle())-180);
	ball.setAngle(newAngle);
	std::cout << "New Angle: " << newAngle << "\n";*/

	// Must set to false so render thread can use it
	game.getWindow()->setActive(false);
	sf::Thread renderThread(&renderLoop, &game);
	renderThread.launch();

	//game.generateLevel(5, 325.0f, false);
	game.generateLevel(5, 550.0f, false);

	sf::Clock clock;
	
	// Main loop | note: rendering is done in another thread | leaves events and logic to main loop
	while (game.getWindow()->isOpen())
    {
        sf::Event event;
        while (game.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
				game.getWindow()->close();
				std::cin.get();
			}
        }

		sf::Time elapsedTime = clock.restart();
		game.eventLoop(elapsedTime.asSeconds());
		game.logicLoop(elapsedTime.asSeconds());
	}

    return 0;
}

void renderLoop(Game* game)
{
	sf::Mouse mouse;
	int x, y;
	while (game->getWindow()->isOpen())
	{
		game->getWindow()->clear();
		game->drawAll();
		game->getWindow()->display();
	}
}

void writeNormal(LineSegment line)
{
	std::cout << "normal: [[" << line.calculateNormal().p1.x << ", " <<
		line.calculateNormal().p1.y << "], [" << line.calculateNormal().p2.x << 
		", " << line.calculateNormal().p2.y << "]]";
}
