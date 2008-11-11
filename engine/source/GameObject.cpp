
// CODESTYLE: v2.0

// GameObject.cpp
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: The base abstract class that all game objects inherit from

#include "GameObject.h"
#include "CommunicationDevice.h"

namespace ENGINE
{
	GameObject::GameObject() :
		comDevice_(0)
	{
		// implement class constructor here
	} // end constructor

	GameObject::~GameObject()
	{
		// implement class destructor here
	} // end destructor


} // end namespace


