
// CODESTYLE: v2.0

// GameObject.h
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: The base abstract class that all game objects inherit from

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

namespace ENGINE
{
	class CommunicationDevice;
	class GameObject
	{
	public:
		// public members should be declared here
		
		// class constructor
		GameObject();
		
		// class destructor
		virtual ~GameObject();
		
		// creates the object
		virtual void Create(CommunicationDevice* comDevice) = 0;
		
		// updates the object
		virtual void Update() = 0;
		
		// renders the object
		virtual void Render() = 0;
		
		// destroys the object
		virtual void Destroy() = 0;
		
		// object to game communication device pointer
		CommunicationDevice* comDevice_;
	}; // end class

} // end namespace
#endif


