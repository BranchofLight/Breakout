#pragma once

// Struct for creating rectangles

/*struct Rect
{	
	float x;
	float y;
	float width;
	float height;
};

bool isRectCollision(Rect r1, Rect r2)
{
	// Calculate the sides of first
	float leftThis = r1.x;
	float rightThis = r1.x + r1.width;
	float topThis = r1.y;
	float bottomThis = r1.y + r1.height;

	 // Calculate the sides of second
	float leftThat = r2.x;
	float rightThat = r2.x + r2.width;
	float topThat = r2.y;
	float bottomThat = r2.y + r2.height;   

	if (bottomThis < topThat)
	{
		return false;
	}

	if (topThis > bottomThat)
	{
		return false;
	}

	if (leftThis < leftThat)
	{
		return false;
	}

	if (rightThis > rightThat)
	{
		return false;
	}
	 
	// Return true if there is a collision
	return true;  
}*/
