#pragma once

#include <SFML\System.hpp>

class LineSegment
{
public:
	LineSegment();
	LineSegment(int, int, int, int);

	LineSegment calculateNormal();
	int** getArray();

	sf::Vector2<int> p1;
	sf::Vector2<int> p2;
};