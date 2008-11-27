
// CODESTYLE: v2.0

// GameObjectGroup.h
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a group of game objects either by ID or name

/**
 * \file GameObjectGroup.h
 * \brief Game Object Module - Header
 */

#ifndef __GAMEOBJECTGROUP_H__
#define __GAMEOBJECTGROUP_H__

#include <vector>
#include <map>
#include <string>

namespace ENGINE
{
	// forward declare classes that we need
	class GameObject;
	
	/**
	 * \class GameObjectGroup
	 * \brief manages a group of game objects either by ID or name
	 */
	class GameObjectGroup
	{
	public:

		/**
		 * class constructor
		 */
		GameObjectGroup();
		
		/**
		 * class destructor
		 */
		~GameObjectGroup();
		
		/**
		 * Calls the Create method on all objects in the group
		 */
		void CallCreate();
		
		/**
		 * Calls the Update method on all objects in the group
		 */
		void CallUpdate();
		
		/**
		 * Calls the Render method on all objects in the group
		 */
		void CallRender();
		
		
		/**
		 * Add a named object to the group
		 * @param objectName is the name for the object to be added
		 * @param object is a pointer to a GameObject to add to the group
		 */
		void AddNamedObject(const char* objectName, GameObject* object);
		
		/**
		 * Gets a named object from the group
		 * @param objectName is the name of the object to retrieve
		 * \return a pointer to a named object or null if the object does not exist
		 */
		GameObject* GetNamedObject(const char* objectName);
		
		/**
		 * Add an object to the group, returns the objectID of the added object
		 * @param object is a pointer to a GameObject to add to the group
		 * \return the object ID for the object you are adding
		 */
		unsigned int AddObject(GameObject* object);
		
		/**
		 * Gets an object from the group by its ID
		 * @param objectID is the ID of the object to retrieve
		 * \return a pointer to an object by ID or null if the object does not exist
		 */
		GameObject* GetObject(unsigned int objectID);
		
		/**
		 * \return the total number of objects (named and not) in the group
		 */
		unsigned int GetObjectCount();
	
		/**
		 * Handles the creation of an instance of this class
		 * \return an allocated pointer to a new instance of the GameObjectGroup class
		 */
		static GameObjectGroup* Create();
		
		/**
		 * Handles the memory release of an instance of this class
		 * @param groupInstance is a pointer to a GameObjectGroup class instance allocated by the GameObjectGroup::Create() function
		 */
		static void Destroy(GameObjectGroup* groupInstance);
		
	private:

		// a few type definitions to make the code easier to read
		
		//! STL vector of GameObject pointers
		typedef std::vector<GameObject*> GameObjectSTLVector;
		
		//! STL iterator for a vector of GameObject pointers
		typedef std::vector<GameObject*>::iterator GameObjectSTLVectorIterator;
		
		//! STL map of string to uints for keeping a lookup index for object names
		typedef std::map<std::string, unsigned int> GameObjectSTLMap;
		
		//! STL iterator for a map of string to uints
		typedef std::map<std::string, unsigned int>::iterator GameObjectSTLMapIterator; 
		
		/**
		 * \var objects_
		 * \brief holds all the objects in the group
		 */
		GameObjectSTLVector objects_;
		
		/**
		 * \var names_
		 * \brief maintains a name index for the named objects
		 *
		 * All objects have an index, but this allows us to access objects by name if
		 * they were added by name
		 */ 
		GameObjectSTLMap names_;
		
	}; // end class

} // end namespace
#endif


