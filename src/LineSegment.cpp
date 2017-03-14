#include "stdafx.h"

LineSegment::LineSegment(int x1, int y1, int x2, int y2)
{
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
}

int** LineSegment::getArray()
{
	int** arr = new int*[2];
	arr[0] = new int[2];
	arr[1] = new int[2];

	arr[0][0] = p1.x;
	arr[0][1] = p1.y;
	arr[1][0] = p2.x;
	arr[1][1] = p2.y;

	return arr;
}

LineSegment LineSegment::calculateNormal()
{
	int deltaX = p2.x - p1.x;
	int deltaY = p2.y - p1.y;

	std::cout << "p1.x: " << p1.x << "\n";
	std::cout << "p1.y: " << p1.y << "\n";
	std::cout << "p2.x: " << p2.x << "\n";
	std::cout << "p2.y: " << p2.y << "\n";

	std::cout << "deltaX: " << deltaX << "\n";
	std::cout << "deltaY: " << deltaY << "\n";

	int** arr = LineSegment(-deltaY, deltaX, deltaY, -deltaX).getArray();
	std::cout << "Normal: [[" << arr[0][0] << ", " <<
		arr[0][1] << "], [" << arr[1][0] << 
		", " << arr[1][1] << "]]";

	delete[] arr[0];
	delete[] arr[1];
	delete[] arr;

	return LineSegment(-deltaY, deltaX, deltaY, -deltaX);
}
