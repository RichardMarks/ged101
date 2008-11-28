
// CODESTYLE: v2.0

// GameState.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: The abstract class that serves as a base for all game states.

/**
 * \file GameState.h
 * \brief Game State Module - Header
 */
#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

namespace ENGINE
{
	/**
	 * \class GameState
	 * \brief The abstract class that serves as a base for all game states.
	 */
	class GameState
	{
	public:
		/**
		 * default constructor
		 */
		GameState(){};
		
		/**
		 * virtual deconstructor
		 */
		virtual ~GameState(){};
		
		/**
		 * Initialize the game state
		 */
		virtual void Initialize() = 0;
		
		/**
		 * The main logic of the game state
		 */
		virtual void Execute() = 0;
		
		/**
		 * Cleanup the game state
		 */
		virtual void Destroy() = 0;
		
	}; // end class

} // end namespace
#endif


