
// CODESTYLE: v2.0

// GameState_Credits.cpp
// Project: Game Engine Design 101 (GAME)
// Author: Richard Marks
// Purpose: The credits game state class.

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "GameState_Credits.h"

// include the game header
#include "Game.h"

// include the game state manager header
#include "GameStateManager.h"

// include the input manager header
#include "InputManager.h"

// include the error reporting header
#include "DebugReport.h"

namespace GAME
{
	/**
	* This is where you should initialize all your member variables.
	* This will be called after the engine is initialized, so you don't
	* have to worry about segfaults due to the engine libs not being init.
	*/
	void GameState_CreditsSingleton::Initialize()
	{
		backgroundImage_ = 0;
		
		// the title bitmap image
		backgroundImage_ = load_bitmap("credits.bmp", 0);
		if (0 == backgroundImage_)
		{
			LogFatal("Could not load credits.bmp!");
		}
	}
	
	/**************************************************************************/
	
	/**
	* This is your place to implement the main logic of your state.
	* Don't forget to call the PopState method of the GameStateManager
	* when you are finished with this state, otherwise you will never
	* be able to exit the game!
	*/
	void GameState_CreditsSingleton::Execute()
	{
		BITMAP* surface = GameInstance->GetBackBuffer();
		bool finished = false;
		while(!finished)
		{
			// make sure we have the right data for the state of input devices.
			ENGINE::InputManager->Update();
			
			// if the user presses the spacebar then exit the credits state
			// if the user presses the escape key then exit the credits state
			if (ENGINE::InputManager->KeyPressed(KEY_SPACE))
			{
				// leave this state
				ENGINE::GameStateManager->PopState();
				finished = true;
			}
			else if (ENGINE::InputManager->KeyPressed(KEY_ESC))
			{
				// leave this state
				ENGINE::GameStateManager->PopState();
				finished = true;
			}
			
			// draw the credits bitmap on the back buffer
			blit(backgroundImage_, surface, 0, 0, 0, 0, backgroundImage_->w, backgroundImage_->h);
			
			// present the scene to the user
			GameInstance->PresentScene();
		}
	}
	
	/**************************************************************************/
	
	/**
	* This is your place to de-allocate anything you allocated in the
	* Initialize method. This method will be called by the state class's
	* destructor. You do not need to call this method directly.
	*/
	void GameState_CreditsSingleton::Destroy()
	{
		if (0 != backgroundImage_) { destroy_bitmap(backgroundImage_); }
	}
	
	/**************************************************************************/
	// THERE IS NO NEED TO MODIFY THE METHODS BELOW THIS LINE!
	/**************************************************************************/
	
	GameState_CreditsSingleton* GameState_CreditsSingleton::GetInstance()
	{
		// return the singleton instance
		static GameState_CreditsSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	GameState_CreditsSingleton::GameState_CreditsSingleton()
	{
		// implement class constructor here
		// DO NOT ALLOCATE MEMBER VARS IN THE CONSTRUCTOR!
		// USE THE Initialize METHOD ONLY!
	} // end constructor
	
	/**************************************************************************/
	
	GameState_CreditsSingleton::~GameState_CreditsSingleton()
	{
		// implement class destructor here
		Destroy();
	} // end destructor
	
	/**************************************************************************/
	
} // end namespace


