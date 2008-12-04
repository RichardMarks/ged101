
// CODESTYLE: v2.0

// GameObjectGroupManager.cpp
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a list of game object groups either by ID or name

/**
 * \file GameObjectGroupManager.cpp
 * \brief Game Object Module - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the complementing header
#include "GameObjectGroupManager.h"

// include the game object group header
#include "GameObjectGroup.h"

namespace ENGINE
{
	GameObjectGroupManager::GameObjectGroupManager()
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
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

	/**************************************************************************/
	
	void GameObjectGroupManager::CallCreate()
	{
		GameObjectGroupSTLVectorIterator iter;
		for (iter = groups_.begin(); iter < groups_.end(); iter++)
		{
			(*iter)->CallCreate();
		}
	}
	
	/**************************************************************************/
	
	void GameObjectGroupManager::CallUpdate()
	{
		GameObjectGroupSTLVectorIterator iter;
		for (iter = groups_.begin(); iter < groups_.end(); iter++)
		{
			(*iter)->CallUpdate();
		}
	}
	
	/**************************************************************************/
	
	void GameObjectGroupManager::CallRender()
	{
		GameObjectGroupSTLVectorIterator iter;
		for (iter = groups_.begin(); iter < groups_.end(); iter++)
		{
			(*iter)->CallRender();
		}
	}

	/**************************************************************************/
	
	void GameObjectGroupManager::CreateNamedGroup(const char* groupName)
	{
		// add a new group to the vector
		groups_.push_back(GameObjectGroup::Create());
		
		// add the name to the index
		names_[groupName] = (unsigned int)groups_.size() - 1;
	}
	
	/**************************************************************************/
	
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
	
	/**************************************************************************/
	
	unsigned int GameObjectGroupManager::CreateGroup()
	{
		// add a new group to the vector
		groups_.push_back(GameObjectGroup::Create());
		
		// return the id for the new group
		return (unsigned int)groups_.size() - 1;
	}
	
	/**************************************************************************/
	
	GameObjectGroup* GameObjectGroupManager::GetGroup(unsigned int groupID)
	{
		return groups_.at(groupID);
	}
	
	/**************************************************************************/
	
	unsigned int GameObjectGroupManager::GetGroupCount()
	{
		return (unsigned int)groups_.size();
	}
	
	/**************************************************************************/
	
	GameObjectGroupManager* GameObjectGroupManager::Create()
	{
		return new GameObjectGroupManager();
	}
	
	/**************************************************************************/
	
	void GameObjectGroupManager::Destroy(GameObjectGroupManager* managerInstance)
	{
		if (0 != managerInstance)
		{
			delete managerInstance;
			managerInstance = 0;
		}
	}

} // end namespace


