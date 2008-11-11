
// CODESTYLE: v2.0

// GameStateManager.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage the run-state of a game.

#ifndef __GAMESTATEMANAGER_H__
#define __GAMESTATEMANAGER_H__

#include <vector>
#include <map>
#include <stack>
#include <string>

namespace ENGINE
{
	/**
	* This class manages the run-state of a game. It accomplishes this by using
	* a stack of pointers to GameState instances.
	*
	* The GameStateManagerSingleton is clearly implemented as a singleton class.
	* Which means that there is only ever a single instance of the class at all times.
	* You access the methods by using the macro "GameStateManager" and a pointer.
	*
	* such as: ENGINE::GameStateManager->ExecuteNextState();
	*
	*/
	class GameState;
	class GameStateManagerSingleton
	{
	public:
		// public members should be declared here
		/**
		* As was stated before, this class is a singleton, and this is the static method
		* that returns the pointer to the singleton instance of the class.
		*/
		static GameStateManagerSingleton* GetInstance();
		
		/**
		* The class destructor handle releasing allocated resources
		*/
		~GameStateManagerSingleton();
		
		/**
		* Returns true if there are no states in the game state stack,
		* and false if there are still states to process.
		*/
		bool Empty();
		
		/**
		* Processes the state that is on the top of the game state stack.
		*/
		void ExecuteNextState();
		
		/**
		* Clears all states from the game state stack.
		*/
		void Clear();
		
		/**
		* Removes the state that is on the top of the game state stack.
		*/
		void PopState();
		
		/**
		* Pushes a new state on to the game state stack.
		*/
		void PushState(const char* stateName);
		
		/**
		* Registers a game state. You need to do this for every state that you
		* will ever use. This will assign both a state ID, and name to a pointer
		* to a game state.
		*/
		void RegisterState(const char* stateName, GameState* stateInstance);
		
		/**
		* Calls the Initialize method on all registered states.
		*/
		void InitializeStates();
		
		/**
		* Returns true if the name passed is assigned to a registered game state
		* and false if the name is not assigned to a registered game state.
		*/
		bool IsStateRegistered(const char* stateName);
		
		/**
		* Clears all game state registrations.
		* Do this if you have a weird need to create a different set of game states
		* at run-time. This will be rare, but the functionality exists just in case.
		*/
		void ClearStateRegistry();
		
		/**
		* Returns the state ID for a given state name.
		* You should always first use IsStateRegistered first to make sure you
		* are trying to get a valid state.
		*/
		unsigned int GetStateID(const char* stateName);
		
		/**
		* Returns a pointer to the game state that is assigned to the state ID.
		* You should not need to use this function directly, but it exists here
		* in case you find a need for it. You should use IsStateRegistered and
		* then GetStateID to make sure you are using a valid state ID.
		*/
		GameState* GetStateFromID(unsigned int stateID);
		
	private:
		// private members should be declared here
		/**
		* The class constructor is private because this is a singleton.
		*/
		GameStateManagerSingleton();
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		GameStateManagerSingleton(const GameStateManagerSingleton& rhs);
		GameStateManagerSingleton& operator=(const GameStateManagerSingleton& rhs);
		
		// a few type definitions to make the code easier to read
		typedef std::stack<GameState*> GameStateSTLStack;
		typedef std::vector<GameState*> GameStateSTLVector;
		typedef std::vector<GameState*>::iterator GameStateSTLVectorIterator;
		typedef std::map<std::string, unsigned int> GameStateSTLMap;
		typedef std::map<std::string, unsigned int>::iterator GameStateSTLMapIterator; 
		
		// holds the current state stack
		GameStateSTLStack stateStack_;
		
		// holds a pointer to all the possible states that the game can be in
		GameStateSTLVector stateRegistry_;
		
		// maintains the name index lookup for the available game states
		GameStateSTLMap names_;
	}; // end class

/**
* The GameStateManager MACRO is the preferred way to use the state manager class singleton pointer.
*/
#define GameStateManager GameStateManagerSingleton::GetInstance()
} // end namespace
#endif


