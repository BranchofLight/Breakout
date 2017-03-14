#include "stdafx.h"

ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager()
{
	disposeAll();
}

void ResourceManager::add(GameObject* obj)
{
	allObjects.push_back(obj);
}

void ResourceManager::remove(GameObject* obj)
{
	for (int i = 0; i < allObjects.size(); i++)
	{
		if (allObjects.at(i) == obj)
		{
			allObjects.erase(allObjects.begin()+i, allObjects.begin()+i+1);
			break;
		}
	}
}

void ResourceManager::remove(int i)
{
	allObjects.erase(allObjects.begin()+i, allObjects.begin()+i+1);
}

void ResourceManager::removeAll()
{
	allObjects.erase(allObjects.begin(), allObjects.end());
}

void ResourceManager::dispose(GameObject* obj)
{
	for (int i = 0; i < allObjects.size(); i++)
	{
		if (allObjects.at(i) == obj)
		{
			GameObject* obj = allObjects.at(i);
			allObjects.erase(allObjects.begin()+i, allObjects.begin()+i+1);
			delete obj;
			break;
		}
	}
}

void ResourceManager::dispose(int i)
{
	GameObject* obj = allObjects.at(i);
	allObjects.erase(allObjects.begin()+i, allObjects.begin()+i+1);
	delete obj;
}

void ResourceManager::disposeAll()
{
	for (int i = 0; i < allObjects.size(); /* no increment because deletion */)
	{
		GameObject* obj = allObjects.at(i);
		allObjects.erase(allObjects.begin()+i, allObjects.begin()+i+1);
		delete obj;
	}
}


unsigned short int ResourceManager::getObjectAmount()
{
	return allObjects.size();
}

GameObject* ResourceManager::getObjectAt(int i)
{
	return allObjects.at(i);
}

