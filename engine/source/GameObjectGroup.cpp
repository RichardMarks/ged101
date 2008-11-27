
// CODESTYLE: v2.0

// GameObjectGroup.cpp
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a group of game objects either by ID or name

/**
 * \file GameObjectGroup.cpp
 * \brief Game Object Module - Implementation
 */

// include the complementing header
#include "GameObjectGroup.h"

// include the game object header
#include "GameObject.h"

namespace ENGINE
{
	GameObjectGroup::GameObjectGroup()
	{
	} // end constructor
	
	/**************************************************************************/
	
	GameObjectGroup::~GameObjectGroup()
	{		
		// delete all objects
		unsigned int index = 0;
		for (index = 0; index < objects_.size(); index++)
		{
			if (0 != objects_[index])
			{
				delete objects_[index];
				objects_[index] = 0;
			}
		}
		objects_.clear();
		
		// clear the named object index
		names_.clear();
		
	} // end destructor
	
	/**************************************************************************/
	
	void GameObjectGroup::CallCreate()
	{
		GameObjectSTLVectorIterator iter;
		for (iter = objects_.begin(); iter < objects_.end(); iter++)
		{
			(*iter)->Create();
		}
	}
	
	/**************************************************************************/
	
	void GameObjectGroup::CallUpdate()
	{
		GameObjectSTLVectorIterator iter;
		for (iter = objects_.begin(); iter < objects_.end(); iter++)
		{
			(*iter)->Update();
		}
	}
	
	/**************************************************************************/
	
	void GameObjectGroup::CallRender()
	{
		GameObjectSTLVectorIterator iter;
		for (iter = objects_.begin(); iter < objects_.end(); iter++)
		{
			(*iter)->Render();
		}
	}
	
	/**************************************************************************/
	
	void GameObjectGroup::AddNamedObject(const char* objectName, GameObject* object)
	{
		// add the object to the vector
		objects_.push_back(object);
		
		// add the name to the index
		names_[objectName] = (unsigned int)objects_.size() - 1;
	}
	
	/**************************************************************************/
	
	GameObject* GameObjectGroup::GetNamedObject(const char* objectName)
	{
		// find the object ID for the named object
		GameObjectSTLMapIterator iter;
		
		if ((iter = names_.find(objectName)) != names_.end())
		{
			// return the object pointer for the named object
			return objects_.at(iter->second);
		}
		
		// object was not found, return null
		return 0;
	}
	
	/**************************************************************************/
	
	unsigned int GameObjectGroup::AddObject(GameObject* object)
	{
		// add the object to the vector
		objects_.push_back(object);
		
		// return the id for the new object
		return (unsigned int)objects_.size() - 1;
	}
	
	/**************************************************************************/
	
	GameObject* GameObjectGroup::GetObject(unsigned int objectID)
	{
		return objects_.at(objectID);
	}
	
	/**************************************************************************/
	
	unsigned int GameObjectGroup::GetObjectCount()
	{
		return (unsigned int)objects_.size();
	}
	
	/**************************************************************************/
	
	GameObjectGroup* GameObjectGroup::Create()
	{
		return new GameObjectGroup();
	}
	
	/**************************************************************************/
	
	void GameObjectGroup::Destroy(GameObjectGroup* groupInstance)
	{
		if (0 != groupInstance)
		{
			delete groupInstance;
			groupInstance = 0;
		}
	}

} // end namespace


