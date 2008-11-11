
// CODESTYLE: v2.0

// GameState_Credits.h
// Project: Game Engine Design 101 (GAME)
// Author: Richard Marks
// Purpose: The credits game state class.

#ifndef __GAMESTATE_CREDITS_H__
#define __GAMESTATE_CREDITS_H__

// include the abstract game state header
#include "GameState.h"

// forward declare the Allegro structures that we will use
struct BITMAP;

namespace GAME
{
	/**
	* This is a game state class.
	* It should hold all information that is specific to this game state.
	*
	* Do not place anything that is supposed to be shared with all states
	* in this class.
	*
	* The GameState_CreditsSingleton is clearly implemented as a singleton class.
	* Which means that there is only ever a single instance of the class at all times.
	* You access the methods by using the macro "GameState_Credits" and a pointer.
	*/
	class GameState_CreditsSingleton : public ENGINE::GameState
	{
	public:
		// public members should be declared here
		
		/**
		* As was stated before, this class is a singleton, and this is the static method
		* that returns the pointer to the singleton instance of the class.
		*/
		static GameState_CreditsSingleton* GetInstance();
		
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
		~GameState_CreditsSingleton();
		
	private:
		// private members should be declared here
		/**
		* The class constructor is private because this is a singleton.
		*/
		GameState_CreditsSingleton();
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		GameState_CreditsSingleton(const GameState_CreditsSingleton& rhs);
		GameState_CreditsSingleton& operator=(const GameState_CreditsSingleton& rhs);
		
		// the credits bitmap image
		BITMAP* backgroundImage_;
		
	}; // end class

/**
* The GameState_Credits MACRO is the preferred way to use the credits game state singleton pointer.
*/
#define GameState_Credits GameState_CreditsSingleton::GetInstance()
} // end namespace
#endif


