
// CODESTYLE: v2.0

// GameObject.h
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: The base abstract class that all game objects inherit from

/**
 * \file GameObject.h
 * \brief Game Object Module - Header
 */
 
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

namespace ENGINE
{
	/**
	 * \class GameObject
	 * \brief The base abstract class that all game objects inherit from
	 */
	class GameObject
	{
	public:
		
		/**
		 * class constructor
		 */
		GameObject();
		
		/**
		 * class destructor
		 */
		virtual ~GameObject();
		
		/**
		 * creates the object
		 */
		virtual void Create() = 0;
		
		/**
		 * updates the object
		 */
		virtual void Update() = 0;
		
		/**
		 * renders the object
		 */
		virtual void Render() = 0;
		
		/**
		 * destroys the object
		 */
		virtual void Destroy() = 0;
		
	}; // end class

} // end namespace
#endif


