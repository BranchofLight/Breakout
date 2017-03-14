#pragma once

#include <SFML\System.hpp>
#include "LineSegment.h"

// This will be part of the physics engine in later games

int dot(sf::Vector2<int>, sf::Vector2<int>);
int calculateAngle(LineSegment, LineSegment);
int normalizeAngle(int);
static const float PI = 3.14159265359;