
// CODESTYLE: v2.0

// GameState_PlayGame.h
// Project: Game Engine Design 101 (GAME)
// Author: Richard Marks
// Purpose: The main game-play game state class.

#ifndef __GAMESTATE_PLAYGAME_H__
#define __GAMESTATE_PLAYGAME_H__

// include the abstract game state header
#include "GameState.h"

namespace GAME
{
	/**
	* This is a game state class.
	* It should hold all information that is specific to this game state.
	*
	* Do not place anything that is supposed to be shared with all states
	* in this class.
	*
	* The GameState_PlayGameSingleton is clearly implemented as a singleton class.
	* Which means that there is only ever a single instance of the class at all times.
	* You access the methods by using the macro "GameState_PlayGame" and a pointer.
	*/
	class GameState_PlayGameSingleton : public ENGINE::GameState
	{
	public:
		// public members should be declared here
		
		/**
		* As was stated before, this class is a singleton, and this is the static method
		* that returns the pointer to the singleton instance of the class.
		*/
		static GameState_PlayGameSingleton* GetInstance();
		
		// implement the GameState interface methods
		
		/**
		* This is where you should initialize all your member variables.
		* This will be called after the engine is initialized, so you don't
		* have to worry about segfaults due to the engine libs not being init.
		*/
		virtual void Initialize();
		
		/**
		* This is your place to implement the main logic of your state.
		* Don't forget to call the PopState method of the GameStateManager
		* when you are finished with this state, otherwise you will never
		* be able to exit the game!
		*/
		virtual void Execute();
		
		/**
		* This is your place to de-allocate anything you allocated in the
		* Initialize method. This method will be called by the state class's
		* destructor. You do not need to call this method directly.
		*/
		virtual void Destroy();
		
		/**
		* class destructor
		*/
		~GameState_PlayGameSingleton();
		
	private:
		// private members should be declared here
		/**
		* The class constructor is private because this is a singleton.
		*/
		GameState_PlayGameSingleton();
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		GameState_PlayGameSingleton(const GameState_PlayGameSingleton& rhs);
		GameState_PlayGameSingleton& operator=(const GameState_PlayGameSingleton& rhs);
		
	}; // end class

/**
* The GameState_PlayGame MACRO is the preferred way to use the game-play game state singleton pointer.
*/
#define GameState_PlayGame GameState_PlayGameSingleton::GetInstance()
} // end namespace
#endif


