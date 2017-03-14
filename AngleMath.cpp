#include "stdafx.h"
#include <math.h>

// This will be part of the physics engine in later games

int dot(sf::Vector2<int> vecA, sf::Vector2<int> vecB)
{
	/*std::cout << "vecA.x: " << vecA.x << std::endl;
	std::cout << "vecA.y: " << vecA.y << std::endl;
	std::cout << "vecB.x: " << vecB.x << std::endl;
	std::cout << "vecB.y: " << vecB.y << std::endl;*/

	return vecA.x*vecB.x + vecA.y*vecB.y;
}

int calculateAngle(LineSegment lineA, LineSegment lineB)
{
	// From an example found online (originally in Python)

	// Get nicer vector form
    sf::Vector2<int> vecA; vecA.x = (lineA.p1.x-lineA.p2.x); vecA.y = (lineA.p1.y-lineA.p2.y);
    sf::Vector2<int> vecB; vecB.x = (lineB.p1.x-lineB.p2.x); vecB.y = (lineB.p1.y-lineB.p2.y);
	//std::cout << "vecA: [ " << vecA.x << ", " << vecA.y << "]\n";
	//std::cout << "vecB: [ " << vecB.x << ", " << vecB.y << "]\n";
    // Get dot prod
    int dot_prod = dot(vecA, vecB);
	//std::cout << "Dot: " << dot_prod << "\n";
    // Get magnitudes
    float magA = pow(dot(vecA, vecA), 0.5f);
    float magB = pow(dot(vecB, vecB), 0.5f);
	//std::cout << "magA: " << magA << "\n";
	//std::cout << "magB: " << magB << "\n";
    // Get cosine value
    float cosineVal = dot_prod/magA/magB;
	//std::cout << "cosine val: " << cosineVal << "\n";
    // Get angle in radians and then convert to degrees
    float ang_rad = acos(dot_prod/magB/magA);
	//std::cout << "ang_rad: " << ang_rad << "\n";
    // Basically doing angle <- angle mod 360
    int ang_deg = ang_rad * (180/PI);
	//std::cout << "ang_deg: " << ang_deg << "\n";

	return normalizeAngle(ang_deg);
    /*if (ang_deg-180 >= 0)
	{
        // As in if statement
        return 360 - ang_deg;
	}
    else
        return ang_deg;*/
}

// Takes an angle and returns it so that it's between 0-360 degrees
int normalizeAngle(int ang)
{
	if (ang < 0)
	{
		while (ang < 0)
			ang += 360;

		return ang;
	}
	else if (ang > 360)
	{
		while (ang > 360)
			ang -= 360;

		return ang;
	}
	
	// Otherwise it's already normalized
	return ang;
}