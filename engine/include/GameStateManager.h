
// CODESTYLE: v2.0

// GameStateManager.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage the run-state of a game.

/**
 * \file GameStateManager.h
 * \brief Game State Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __GAMESTATEMANAGER_H__
#define __GAMESTATEMANAGER_H__

#include <vector>
#include <map>
#include <stack>
#include <string>

namespace ENGINE
{
	// forward declare the classes we need
	class GameState;
	
	/**
	 * \class GameStateManagerSingleton
	 * \brief A class to manage the run-state of a game.
	 * \ingroup SystemGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 *
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
	class GameStateManagerSingleton
	{
	public:

		/**
		 * \return a pointer to the singleton class
		 */
		static GameStateManagerSingleton* GetInstance();
		
		/**
		 * De-allocates any allocated memory
		 */
		~GameStateManagerSingleton();
		
		/**
		 * \return true if there are no states in the game state stack, and false if there are still states to process.
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
		 * @param stateName is the name of the registered game state to push
		 */
		void PushState(const char* stateName);
		
		/**
		 * Registers a game state. You need to do this for every state that you
		 * will ever use. This will assign both a state ID, and name to a pointer
		 * to a game state.
		 * @param stateName is the name to register the state to
		 * @param stateInstance is a pointer to the singleton class for the state to register
		 */
		void RegisterState(const char* stateName, GameState* stateInstance);
		
		/**
		 * Calls the Initialize method on all registered states.
		 */
		void InitializeStates();
		
		/**
		 * Check if a state is registered
		 * @param stateName is the name of the state to check
		 * \return true if the name passed is assigned to a registered game state and false if the name is not assigned to a registered game state.
		 */
		bool IsStateRegistered(const char* stateName);
		
		/**
		 * Clears all game state registrations.
		 * Do this if you have a weird need to create a different set of game states
		 * at run-time. This will be rare, but the functionality exists just in case.
		 */
		void ClearStateRegistry();
		
		/**
		 * Get the ID for a registered state
		 * You should always first use IsStateRegistered first to make sure you
		 * are trying to get a valid state.
		 * @param stateName is the name of the state to get the ID for
		 * \return the state ID for a given state name.
		 */
		unsigned int GetStateID(const char* stateName);
		
		/**
		 * Get a state by its ID
		 * You should not need to use this function directly, but it exists here
		 * in case you find a need for it. You should use IsStateRegistered and
		 * then GetStateID to make sure you are using a valid state ID.
		 * @param stateID is the ID for the state you want
		 * \return a pointer to the game state that is assigned to the state ID.
		 */
		GameState* GetStateFromID(unsigned int stateID);
		
	private:
	
		/**
		 * hidden default constructor
		 */
		GameStateManagerSingleton();
		
		/**
		 * hidden copy constructor
		 */
		GameStateManagerSingleton(const GameStateManagerSingleton& rhs);
		
		/**
		 * hidden assignment operator
		 */
		GameStateManagerSingleton& operator=(const GameStateManagerSingleton& rhs);
		
		// a few type definitions to make the code easier to read
		
		//! an STL stack of pointers to the GameState class
		typedef std::stack<GameState*> GameStateSTLStack;
		
		//! an STL vector of pointers to the GameState class
		typedef std::vector<GameState*> GameStateSTLVector;
		
		//! an STL iterator to a vector of pointers to the GameState class
		typedef std::vector<GameState*>::iterator GameStateSTLVectorIterator;
		
		//! an STL map for keeping a lookup index
		typedef std::map<std::string, unsigned int> GameStateSTLMap;
		
		//! an STL iterator for the lookup index
		typedef std::map<std::string, unsigned int>::iterator GameStateSTLMapIterator; 
		
		/**
		 * \var stateStack_
		 * \brief holds the current state stack
		 */
		GameStateSTLStack stateStack_;
		
		/**
		 * \var stateRegistry_
		 * \brief holds a pointer to all the possible states that the game can be in
		 */
		GameStateSTLVector stateRegistry_;
		
		/**
		 * \var names_
		 * \brief maintains the name index lookup for the available game states
		 */
		GameStateSTLMap names_;
	}; // end class

/**
 * \def GameStateManager
 * \brief an alias to GameStateManagerSingleton::GetInstance()
 */
#define GameStateManager GameStateManagerSingleton::GetInstance()
} // end namespace
#endif


