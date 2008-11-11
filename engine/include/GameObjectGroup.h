
// CODESTYLE: v2.0

// GameObjectGroup.h
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a group of game objects either by ID or name

#ifndef __GAMEOBJECTGROUP_H__
#define __GAMEOBJECTGROUP_H__

#include <vector>
#include <map>
#include <string>

namespace ENGINE
{
	class CommunicationDevice;
	class GameObject;
	class GameObjectGroup
	{
	public:
		// public members should be declared here

		// class constructor
		GameObjectGroup();
		
		// class destructor
		~GameObjectGroup();
		
		//#### BEGIN Method Callers
		// calls the Create method on all objects in the group
		void CallCreate(CommunicationDevice* comDevice);
		
		// calls the Update method on all objects in the group
		void CallUpdate();
		
		// calls the Render method on all objects in the group
		void CallRender();
		//#### END Method Callers
		
		
		// add a named object to the group
		void AddNamedObject(const char* objectName, GameObject* object);
		
		// returns a pointer to a named object or null if the object does not exist
		GameObject* GetNamedObject(const char* objectName);
		
		// add an object to the group, returns the objectID of the added object
		unsigned int AddObject(GameObject* object);
		
		// returns a pointer to an object by ID or null if the object does not exist
		GameObject* GetObject(unsigned int objectID);
		
		// returns the total number of objects (named and not) in the group
		unsigned int GetObjectCount();
	
		// handles the creation of an instance of this class
		static GameObjectGroup* Create();
		
		// handles the memory release of an instance of this class
		static void Destroy(GameObjectGroup* groupInstance);
		
	private:
		// private members should be declared here
		
		// a few type definitions to make the code easier to read
		typedef std::vector<GameObject*> GameObjectSTLVector;
		typedef std::vector<GameObject*>::iterator GameObjectSTLVectorIterator;
		typedef std::map<std::string, unsigned int> GameObjectSTLMap;
		typedef std::map<std::string, unsigned int>::iterator GameObjectSTLMapIterator; 
		
		// holds all the objects in the group
		GameObjectSTLVector objects_;
		
		// maintains a name index for the named objects
		// all objects have an index, but this allows us to access objects by name if
		// they were added by name
		GameObjectSTLMap names_;
		
		
	}; // end class

} // end namespace
#endif


