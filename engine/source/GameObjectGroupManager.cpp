
// CODESTYLE: v2.0

// GameObjectGroupManager.cpp
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a list of game object groups either by ID or name

#include "GameObjectGroupManager.h"
#include "GameObjectGroup.h"
#include "CommunicationDevice.h"

namespace ENGINE
{
	GameObjectGroupManager::GameObjectGroupManager()
	{
		// implement class constructor here
	} // end constructor

	GameObjectGroupManager::~GameObjectGroupManager()
	{
		// implement class destructor here
		
		// delete all groups
		unsigned int index = 0;
		for (index = 0; index < groups_.size(); index++)
		{
			if (0 != groups_[index])
			{
				delete groups_[index];
				groups_[index] = 0;
			}
		}
		groups_.clear();
		
		// clear the named group index
		names_.clear();
	} // end destructor

	// calls the CallCreate method on all groups in the list
	void GameObjectGroupManager::CallCreate(CommunicationDevice* comDevice)
	{
		GameObjectGroupSTLVectorIterator iter;
		for (iter = groups_.begin(); iter < groups_.end(); iter++)
		{
			(*iter)->CallCreate(comDevice);
		}
	}
	
	// calls the CallUpdate method on all groups in the list
	void GameObjectGroupManager::CallUpdate()
	{
		GameObjectGroupSTLVectorIterator iter;
		for (iter = groups_.begin(); iter < groups_.end(); iter++)
		{
			(*iter)->CallUpdate();
		}
	}
	
	// calls the CallRender method on all groups in the list
	void GameObjectGroupManager::CallRender()
	{
		GameObjectGroupSTLVectorIterator iter;
		for (iter = groups_.begin(); iter < groups_.end(); iter++)
		{
			(*iter)->CallRender();
		}
	}

	// creates a new named group
	void GameObjectGroupManager::CreateNamedGroup(const char* groupName)
	{
		// add a new group to the vector
		groups_.push_back(GameObjectGroup::Create());
		
		// add the name to the index
		names_[groupName] = (unsigned int)groups_.size() - 1;
	}
	
	// returns a pointer to a named group or null if the group does not exist
	GameObjectGroup* GameObjectGroupManager::GetNamedGroup(const char* groupName)
	{
		// find the group ID for the named group
		GameObjectGroupSTLMapIterator iter;
		
		if ((iter = names_.find(groupName)) != names_.end())
		{
			// return the group pointer for the named group
			return groups_.at(iter->second);
		}
		
		// group was not found, return null
		return 0;
	}
	
	// create a new group, returns the ID of the new group
	unsigned int GameObjectGroupManager::CreateGroup()
	{
		// add a new group to the vector
		groups_.push_back(GameObjectGroup::Create());
		
		// return the id for the new group
		return (unsigned int)groups_.size() - 1;
	}
	
	// returns a pointer to a group or null if the group does not exist
	GameObjectGroup* GameObjectGroupManager::GetGroup(unsigned int groupID)
	{
		return groups_.at(groupID);
	}
	
	// returns the total number of groups in the list
	unsigned int GameObjectGroupManager::GetGroupCount()
	{
		return (unsigned int)groups_.size();
	}
	
	// handles the creation of an instance of this class
	GameObjectGroupManager* GameObjectGroupManager::Create()
	{
		return new GameObjectGroupManager();
	}
	
	// handles the memory release of an instance of this class
	void GameObjectGroupManager::Destroy(GameObjectGroupManager* managerInstance)
	{
		if (0 != managerInstance)
		{
			delete managerInstance;
			managerInstance = 0;
		}
	}

} // end namespace


