// Class objectives:
// - Hold and manage all objects that the game contains
// MAYBE: Have functions to allow concurrent data between new levels (eg. same active powerups still active, etc)

#pragma once;

#include <vector>
#include "GameObject.h"
#include "Ball.h"
#include "Paddle.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void add(GameObject*);

	// Remove the object from the list
	void remove(GameObject*);
	void remove(int);
	void removeAll();

	// Remove and DELETE the object
	void dispose(GameObject*);
	void dispose(int);
	void disposeAll();

	unsigned short int getObjectAmount();
	GameObject*        getObjectAt(int);

private:
	// List of all objects
	std::vector<GameObject*> allObjects;	
};