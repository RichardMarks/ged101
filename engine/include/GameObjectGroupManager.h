
// CODESTYLE: v2.0

// GameObjectGroupManager.h
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a list of game object groups either by ID or name

#ifndef __GAMEOBJECTGROUPMANAGER_H__
#define __GAMEOBJECTGROUPMANAGER_H__

#include <vector>
#include <map>
#include <string>

namespace ENGINE
{
	class CommunicationDevice;
	class GameObjectGroup;
	class GameObjectGroupManager
	{
	public:
		// public members should be declared here

		// class constructor
		GameObjectGroupManager();
		
		// class destructor
		~GameObjectGroupManager();
		
		//#### BEGIN Method Callers
		// calls the CallCreate method on all groups in the list
		void CallCreate(CommunicationDevice* comDevice);
		
		// calls the CallUpdate method on all groups in the list
		void CallUpdate();
		
		// calls the CallRender method on all groups in the list
		void CallRender();
		//#### END Method Callers
		
		// creates a new named group
		void CreateNamedGroup(const char* groupName);
		
		// returns a pointer to a named group or null if the group does not exist
		GameObjectGroup* GetNamedGroup(const char* groupName);
		
		// create a new group, returns the ID of the new group
		unsigned int CreateGroup();
		
		// returns a pointer to a group or null if the group does not exist
		GameObjectGroup* GetGroup(unsigned int groupID);
		
		// returns the total number of groups in the list
		unsigned int GetGroupCount();
		
		// handles the creation of an instance of this class
		static GameObjectGroupManager* Create();
		
		// handles the memory release of an instance of this class
		static void Destroy(GameObjectGroupManager* managerInstance);
		
	private:
		// private members should be declared here
		
		// a few type definitions to make the code easier to read
		typedef std::vector<GameObjectGroup*> GameObjectGroupSTLVector;
		typedef std::vector<GameObjectGroup*>::iterator GameObjectGroupSTLVectorIterator;
		typedef std::map<std::string, unsigned int> GameObjectGroupSTLMap;
		typedef std::map<std::string, unsigned int>::iterator GameObjectGroupSTLMapIterator; 
		
		// holds all the groups in the list
		GameObjectGroupSTLVector groups_;
		
		// maintains a name index for the named groups
		// all groups have an index, but this allows us to access groups by name if
		// they were added by name
		GameObjectGroupSTLMap names_;
	}; // end class

} // end namespace
#endif


