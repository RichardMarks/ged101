
// CODESTYLE: v2.0

// GameObjectGroup.cpp
// Project: Game Engine Design 101 Project (ENGINE)
// Author: Richard Marks
// Purpose: manages a group of game objects either by ID or name

#include "GameObjectGroup.h"
#include "GameObject.h"
#include "CommunicationDevice.h"

namespace ENGINE
{
	GameObjectGroup::GameObjectGroup()
	{
		// implement class constructor here
	} // end constructor

	GameObjectGroup::~GameObjectGroup()
	{
		// implement class destructor here
		
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

	// calls the Create method on all objects in the group
	void GameObjectGroup::CallCreate(CommunicationDevice* comDevice)
	{
		GameObjectSTLVectorIterator iter;
		for (iter = objects_.begin(); iter < objects_.end(); iter++)
		{
			(*iter)->Create(comDevice);
		}
	}
	
	// calls the Update method on all objects in the group
	void GameObjectGroup::CallUpdate()
	{
		GameObjectSTLVectorIterator iter;
		for (iter = objects_.begin(); iter < objects_.end(); iter++)
		{
			(*iter)->Update();
		}
	}
	
	// calls the Render method on all objects in the group
	void GameObjectGroup::CallRender()
	{
		GameObjectSTLVectorIterator iter;
		for (iter = objects_.begin(); iter < objects_.end(); iter++)
		{
			(*iter)->Render();
		}
	}
	

	// add a named object to the group
	void GameObjectGroup::AddNamedObject(const char* objectName, GameObject* object)
	{
		// add the object to the vector
		objects_.push_back(object);
		
		// add the name to the index
		names_[objectName] = (unsigned int)objects_.size() - 1;
	}
	
	// returns a pointer to a named object or null if the object does not exist
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
	
	// add an object to the group, returns the objectID of the added object
	unsigned int GameObjectGroup::AddObject(GameObject* object)
	{
		// add the object to the vector
		objects_.push_back(object);
		
		// return the id for the new object
		return (unsigned int)objects_.size() - 1;
	}
	
	// returns a pointer to an object by ID or null if the object does not exist
	GameObject* GameObjectGroup::GetObject(unsigned int objectID)
	{
		return objects_.at(objectID);
	}
	
	// returns the total number of objects (named and not) in the group
	unsigned int GameObjectGroup::GetObjectCount()
	{
		return (unsigned int)objects_.size();
	}
	
	// handles the creation of an instance of this class
	GameObjectGroup* GameObjectGroup::Create()
	{
		return new GameObjectGroup();
	}
	
	// handles the memory release of an instance of this class
	void GameObjectGroup::Destroy(GameObjectGroup* groupInstance)
	{
		if (0 != groupInstance)
		{
			delete groupInstance;
			groupInstance = 0;
		}
	}

} // end namespace


