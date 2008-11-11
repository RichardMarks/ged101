
// CODESTYLE: v2.0

// GameStateManager.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage the run-state of a game.

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

	/**
	* Returns true if there are no states in the game state stack,
	* and false if there are still states to process.
	*/
	bool GameStateManagerSingleton::Empty()
	{
		return stateStack_.empty();
	}
	
	/**************************************************************************/

	/**
	* Processes the state that is on the top of the game state stack.
	*/
	void GameStateManagerSingleton::ExecuteNextState()
	{
		stateStack_.top()->Execute();		
	}
	
	/**************************************************************************/

	/**
	* Clears all states from the game state stack.
	*/
	void GameStateManagerSingleton::Clear()
	{
		while (!stateStack_.empty())
		{
			stateStack_.pop();
		}
	}
	
	/**************************************************************************/

	/**
	* Removes the state that is on the top of the game state stack.
	*/
	void GameStateManagerSingleton::PopState()
	{
		stateStack_.pop();
	}
	
	/**************************************************************************/

	/**
	* Pushes a new state on to the game state stack.
	*/
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

	/**
	* Registers a game state. You need to do this for every state that you
	* will ever use. This will assign both a state ID, and name to a pointer
	* to a game state.
	*/
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

	/**
	* Calls the Initialize method on all registered states.
	*/
	void GameStateManagerSingleton::InitializeStates()
	{
		GameStateSTLVectorIterator iter;
		for (iter = stateRegistry_.begin(); iter < stateRegistry_.end(); iter++)
		{
			(*iter)->Initialize();
		}
	}
	
	/**************************************************************************/

	/**
	* Returns true if the name passed is assigned to a registered game state
	* and false if the name is not assigned to a registered game state.
	*/
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

	/**
	* Clears all game state registrations.
	* Do this if you have a weird need to create a different set of game states
	* at run-time. This will be rare, but the functionality exists just in case.
	*/
	void GameStateManagerSingleton::ClearStateRegistry()
	{
		// clear the registry vector
		stateRegistry_.clear();
		
		// clear the name index
		names_.clear();
	}
	
	/**************************************************************************/

	/**
	* Returns the state ID for a given state name.
	* You should always first use IsStateRegistered first to make sure you
	* are trying to get a valid state.
	*/
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

	/**
	* Returns a pointer to the game state that is assigned to the state ID.
	* You should not need to use this function directly, but it exists here
	* in case you find a need for it. You should use IsStateRegistered and
	* then GetStateID to make sure you are using a valid state ID.
	*/
	GameState* GameStateManagerSingleton::GetStateFromID(unsigned int stateID)
	{
		return stateRegistry_.at(stateID);
	}
	

} // end namespace


