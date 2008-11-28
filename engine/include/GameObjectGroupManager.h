
// CODESTYLE: v2.0

// GameObjectGroupManager.h
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a list of game object groups either by ID or name

/**
 * \file GameObjectGroupManager.h
 * \brief Game Object Module - Header
 */

#ifndef __GAMEOBJECTGROUPMANAGER_H__
#define __GAMEOBJECTGROUPMANAGER_H__

#include <vector>
#include <map>
#include <string>

namespace ENGINE
{
	// forward declare classes that we need
	class GameObjectGroup;

	/**
	 * \class GameObjectGroupManager
	 * \brief A class to manage a list of game object groups either by ID or name
	 * \ingroup Object Management
	 */
	class GameObjectGroupManager
	{
	public:

		/**
		 * default constructor
		 */
		GameObjectGroupManager();
		
		/**
		 * class destructor
		 */
		~GameObjectGroupManager();
		
		/**
		 * Calls the CallCreate method on all groups in the list
		 */
		void CallCreate();
		
		/**
		 * Calls the CallUpdate method on all groups in the list
		 */
		void CallUpdate();
		
		/**
		 * Calls the CallRender method on all groups in the list
		 */
		void CallRender();
		
		/**
		 * Creates a new named group
		 * @param groupName is the name to assign to a new GameObjectGroup
		 */
		void CreateNamedGroup(const char* groupName);
		
		/**
		 * Get a group by its name
		 * @param groupName is the name of the group to get
		 * \return a pointer to a named group or null if the group does not exist
		 */
		GameObjectGroup* GetNamedGroup(const char* groupName);
		
		/**
		 * Create a new group
		 * \return the group ID for a new GameObjectGroup
		 */
		unsigned int CreateGroup();
		
		/**
		 * Get a group by its ID
		 * @param groupID is the ID for the group you want
		 * \return a pointer to a group or null if the group does not exist
		 */
		GameObjectGroup* GetGroup(unsigned int groupID);
		
		/**
		 * \return the total number of groups in the list
		 */
		unsigned int GetGroupCount();
		
		/**
		 * Handles the creation of an instance of this class
		 * \return a pointer to an allocated instance of the GameObjectGroupManager class
		 */
		static GameObjectGroupManager* Create();
		
		/**
		 * Handles the memory release of an instance of this class
		 * @param managerInstance is a pointer to an allocated instance of the GameObjectGroupManager class
		 */
		static void Destroy(GameObjectGroupManager* managerInstance);
		
	private:
	
		// a few type definitions to make the code easier to read
		
		//! an STL vector of pointers to the GameObjectGroup class
		typedef std::vector<GameObjectGroup*> GameObjectGroupSTLVector;
		
		//! an STL iterator to a vector of GameObjectGroup class pointers
		typedef std::vector<GameObjectGroup*>::iterator GameObjectGroupSTLVectorIterator;
		
		//! an STL map for keeping a lookup index 
		typedef std::map<std::string, unsigned int> GameObjectGroupSTLMap;
		
		//! an STL iterator for the lookup index
		typedef std::map<std::string, unsigned int>::iterator GameObjectGroupSTLMapIterator; 
		
		/**
		 * \var groups_
		 * \brief Holds all the groups in the list
		 */
		GameObjectGroupSTLVector groups_;
		
		/**
		 * \var names_
		 * \brief maintains a name index for the named groups
		 * all groups have an index, but this allows us to access groups by name if
		 * they were added by name
		 */
		GameObjectGroupSTLMap names_;
	}; // end class

} // end namespace
#endif


