
// CODESTYLE: v2.0

// GameStateManager.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage the run-state of a game.

/**
 * \file GameStateManager.cpp
 * \brief Game State Module - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include the complementing header
#include "GameStateManager.h"

// include the abstract game state header
#include "GameState.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	GameStateManagerSingleton* GameStateManagerSingleton::GetInstance()
	{
		// return the singleton instance
		static GameStateManagerSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	GameStateManagerSingleton::GameStateManagerSingleton()
	{
		// implement class constructor here
	} // end constructor

	/**************************************************************************/
	
	GameStateManagerSingleton::~GameStateManagerSingleton()
	{
		// implement class destructor here
		ClearStateRegistry();
	} // end destructor

	/**************************************************************************/

	bool GameStateManagerSingleton::Empty()
	{
		return stateStack_.empty();
	}
	
	/**************************************************************************/

	void GameStateManagerSingleton::ExecuteNextState()
	{
		stateStack_.top()->Execute();		
	}
	
	/**************************************************************************/

	void GameStateManagerSingleton::Clear()
	{
		while (!stateStack_.empty())
		{
			stateStack_.pop();
		}
	}
	
	/**************************************************************************/

	void GameStateManagerSingleton::PopState()
	{
		stateStack_.pop();
	}
	
	/**************************************************************************/

	void GameStateManagerSingleton::PushState(const char* stateName)
	{
		if (IsStateRegistered(stateName))
		{
			stateStack_.push(GetStateFromID(GetStateID(stateName)));
		}
		else
		{
			unsigned int errStateLen = strlen(stateName);
			char errMsg[128 + errStateLen];
			sprintf(errMsg, "The Game State [%s] was not registered!\n", stateName);
			LogError(errMsg);
		}
	}
	
	/**************************************************************************/

	void GameStateManagerSingleton::RegisterState(const char* stateName, GameState* stateInstance)
	{
		// check that the state is not already registered
		// search the name index for state name
		GameStateSTLMapIterator iter;
		
		if (!((iter = names_.find(stateName)) != names_.end()))
		{
			// add the state to the registry
			stateRegistry_.push_back(stateInstance);
			
			// add the state id to the name index
			names_[stateName] = static_cast<unsigned int>(stateRegistry_.size() - 1);
		}
		else
		{
			unsigned int errStateLen = strlen(stateName);
			char errMsg[128 + errStateLen];
			sprintf(errMsg, 
				"The Game State [%s] is already registered!\n"
				"\tYou cannot register the same state twice!\n", stateName);
			LogError(errMsg);
		}
	}
	
	/**************************************************************************/

	void GameStateManagerSingleton::InitializeStates()
	{
		GameStateSTLVectorIterator iter;
		for (iter = stateRegistry_.begin(); iter < stateRegistry_.end(); iter++)
		{
			(*iter)->Initialize();
		}
	}
	
	/**************************************************************************/

	bool GameStateManagerSingleton::IsStateRegistered(const char* stateName)
	{
		// search the name index for state name
		GameStateSTLMapIterator iter;
		
		if ((iter = names_.find(stateName)) != names_.end())
		{
			return true;
		}
		else
		{
			unsigned int errStateLen = strlen(stateName);
			char errMsg[128 + errStateLen];
			sprintf(errMsg, 
				"The Game State [%s] is not registered!\n", stateName);
			LogError(errMsg);
		}
		return false;
	}
	
	/**************************************************************************/

	void GameStateManagerSingleton::ClearStateRegistry()
	{
		// clear the registry vector
		stateRegistry_.clear();
		
		// clear the name index
		names_.clear();
	}
	
	/**************************************************************************/

	unsigned int GameStateManagerSingleton::GetStateID(const char* stateName)
	{
		// search the name index for state name and return the assigned state ID
		GameStateSTLMapIterator iter;
		
		if ((iter = names_.find(stateName)) != names_.end())
		{
			return static_cast<unsigned int>(iter->second);
		}
		else
		{
			unsigned int errStateLen = strlen(stateName);
			char errMsg[128 + errStateLen];
			sprintf(errMsg, 
				"The Game State [%s] was not registered!\n"
				"\tThe stateID 0 (zero) was returned.\n"
				"\tThis possibly is NOT what you wanted.\n", stateName);
			LogError(errMsg);
		}
		return 0;
	}
	
	/**************************************************************************/

	GameState* GameStateManagerSingleton::GetStateFromID(unsigned int stateID)
	{
		return stateRegistry_.at(stateID);
	}
	

} // end namespace


