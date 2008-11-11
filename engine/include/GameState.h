
// CODESTYLE: v2.0

// GameState.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: The abstract class that serves as a base for all game states.

#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

namespace ENGINE
{
	class GameState
	{
	public:
		// public members should be declared here
		GameState(){};
		virtual ~GameState(){};
		
		virtual void Initialize() = 0;
		virtual void Execute() = 0;
		virtual void Destroy() = 0;
		
	}; // end class

} // end namespace
#endif


