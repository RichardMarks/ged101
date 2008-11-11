
// CODESTYLE: v2.0

// Game.cpp
// Project: Game Engine Design 101 (GAME)
// Author: Richard Marks
// Purpose: This is your game's primary class. It should hold all information that is shared between game states.

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "Game.h"

// include the game state manager header
#include "GameStateManager.h"

// include the headers for each game state that you will ever use
#include "GameState_Title.h"
#include "GameState_Credits.h"
//#include "GameState_MainMenu.h"
#include "GameState_PlayGame.h"
//#include "GameState_Paused.h"
//#include "GameState_GameWin.h"
//#include "GameState_GameOver.h"

namespace GAME
{
	GameSingleton* GameSingleton::GetInstance()
	{
		// return the singleton instance
		static GameSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	GameSingleton::GameSingleton() :
		backBuffer_(0)
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	GameSingleton::~GameSingleton()
	{
		// implement class destructor here
		
		// the de-allocation of the back buffer pointer is not handled by this
		// class, rather it is handled by the ALBASEMain class.
		
		// de-allocate any member variables that you allocated in the Initialize method here.
		
		// for instance:
		// if (0 != saveState_) { delete saveState_; saveState_ = 0; }
		
	} // end destructor
	
	/**************************************************************************/
	
	/**
	* Initializes all member variables, registers the game states, and
	* calls Initialize on all game states.
	*/
	void GameSingleton::Initialize()
	{
		// initialize any member variables that you need to be able to share
		// with the game states here. Always do this before they are registered.
		
		// for instance:
		// saveState_ = new ENGINE::SaveState("game.sav");
		
		// register the game states
		ENGINE::GameStateManager->RegisterState("title", GameState_Title);
		ENGINE::GameStateManager->RegisterState("credits", GameState_Credits);
		ENGINE::GameStateManager->RegisterState("play game", GameState_PlayGame);
		
		// initialize the game states
		ENGINE::GameStateManager->InitializeStates();
		
		// push the states that you need to start the game here.
		/*
			Be sure that you think of it as a LIFO container.
			That means the last state that you push, will be the first state
			that will be executed.
			
			
			In this case, the credits state will be executed AFTER the title has finished:
		*/

		ENGINE::GameStateManager->PushState("credits");
		ENGINE::GameStateManager->PushState("title");
	}
	
	/**************************************************************************/
	
	/**
	* This is called by the ALBASEMain class, so that your game
	* has access to the back buffer surface.
	*/
	void GameSingleton::SetRenderTarget(BITMAP* target)
	{
		// can only call this method ONCE
		static bool firstCall = true;
		if (firstCall)
		{
			// set the pointer
			backBuffer_ = target;
			
			// prevent this code from executing again
			firstCall = false;
		}
	}
	
	/**************************************************************************/
	
	/**
	* This method copies the contents of the back buffer surface to the screen.
	*/
	void GameSingleton::PresentScene()
	{
		blit(backBuffer_, screen, 0, 0, 0, 0, backBuffer_->w, backBuffer_->h);
	}
	
	/**************************************************************************/
	
	/**
	* This gives your game states access to the back buffer surface pointer.
	*/
	BITMAP* GameSingleton::GetBackBuffer()
	{
		return backBuffer_;
	}
	
} // end namespace


