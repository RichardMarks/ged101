
// CODESTYLE: v2.0

// Game.h
// Project: Game Engine Design 101 (GAME)
// Author: Richard Marks
// Purpose: This is your game's primary class. It should hold all information that is shared between game states.

#ifndef __GAME_H__
#define __GAME_H__

struct BITMAP;

namespace GAME
{
	/**
	* This is your game's primary class. 
	* It should hold all information that is shared between game states.
	*
	* Do not place anything that is game state specific in this class.
	*
	* The GameSingleton is clearly implemented as a singleton class.
	* Which means that there is only ever a single instance of the class at all times.
	* You access the methods by using the macro "GameInstance" and a pointer.
	*/
	class GameSingleton
	{
	public:
		// public members should be declared here
		
		/**
		* As was stated before, this class is a singleton, and this is the static method
		* that returns the pointer to the singleton instance of the class.
		*/
		static GameSingleton* GetInstance();
		
		/**
		* The class destructor handle releasing allocated resources
		*/
		~GameSingleton();
		
		/**
		* Initializes all member variables, registers the game states, and
		* calls Initialize on all game states.
		*/
		void Initialize();
		
		/**
		* This is called by the ALBASEMain class, so that your game
		* has access to the back buffer surface.
		*/
		void SetRenderTarget(BITMAP* target);
		
		/**
		* This method copies the contents of the back buffer surface to the screen
		*/
		void PresentScene();
		
		/**
		* This gives your game states access to the back buffer surface pointer.
		*/
		BITMAP* GetBackBuffer();
		
	private:
		// private members should be declared here
		/**
		* The class constructor is private because this is a singleton.
		*/
		GameSingleton();
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		GameSingleton(const GameSingleton& rhs);
		GameSingleton& operator=(const GameSingleton& rhs);
		
		// this is the back buffer surface pointer that is set by the SetRenderTarget method.
		BITMAP* backBuffer_;
		
	}; // end class

/**
* The GameInstance MACRO is the preferred way to use the game class singleton pointer.
*/
#define GameInstance GameSingleton::GetInstance()
} // end namespace
#endif


