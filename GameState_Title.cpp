
// CODESTYLE: v2.0

// GameState_Title.cpp
// Project: Game Engine Design 101 (GAME)
// Author: Richard Marks
// Purpose: The title game state class.

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "GameState_Title.h"

// include the game header
#include "Game.h"

// include the game state manager header
#include "GameStateManager.h"

// include the input manager header
#include "InputManager.h"

// include the error reporting header
#include "DebugReport.h"

// include the audio formats header
#include "AudioFormats.h"

// include the audio engine header 
#include "Audio.h"

// include the headers for each game state that you 
// will ever need to use from this state here
// #include "GameState_MainMenu.h"
#include "GameState_PlayGame.h"

namespace GAME
{
	/**
	* This is where you should initialize all your member variables.
	* This will be called after the engine is initialized, so you don't
	* have to worry about segfaults due to the engine libs not being init.
	*/
	void GameState_TitleSingleton::Initialize()
	{
		backgroundImage_ = 0;
		backgroundMusic_ = 0;
		startSound_ = 0;
		exitSound_ = 0;
		
		// the title bitmap image
		backgroundImage_ = load_bitmap("title.bmp", 0);
		if (0 == backgroundImage_)
		{
			LogFatal("Could not load title.bmp!");
		}
		
		// the title background music
		backgroundMusic_ = ENGINE::Audio::GetStream_OGG("title.ogg", 255, 128, 1);
		if (0 == backgroundMusic_)
		{
			LogFatal("Could not load title.ogg!");
		}
		
		// the sound effects that play when you start or exit the game
		exitSound_ = load_sample("cancel.wav");
		if (0 == exitSound_)
		{
			LogFatal("Could not load cancel.wav!");
		}
		
		startSound_ = load_sample("accept.wav");
		if (0 == startSound_)
		{
			LogFatal("Could not load accept.wav!");
		}
	}
	
	/**************************************************************************/
	
	/**
	* This is your place to implement the main logic of your state.
	* Don't forget to call the PopState method of the GameStateManager
	* when you are finished with this state, otherwise you will never
	* be able to exit the game!
	*/
	void GameState_TitleSingleton::Execute()
	{
		BITMAP* surface = GameInstance->GetBackBuffer();
		bool finished = false;
		while(!finished)
		{
			// update the audio stream
			ENGINE::Audio::UpdateStream_OGG(backgroundMusic_);
			
			// make sure we have the right data for the state of input devices.
			ENGINE::InputManager->Update();
			
			// if the user presses the spacebar then start the game
			// if the user presses the escape key then exit the title state
			if (ENGINE::InputManager->KeyPressed(KEY_SPACE))
			{
				// start the game
				ENGINE::Audio::StopStream_OGG(backgroundMusic_);
				ENGINE::GameStateManager->PushState("play game");
				finished = true;
			}
			else if (ENGINE::InputManager->KeyPressed(KEY_ESC))
			{
				// leave this state
				ENGINE::Audio::StopStream_OGG(backgroundMusic_);
				ENGINE::GameStateManager->PopState();
				finished = true;
			}
			
			// draw the title bitmap on the back buffer
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
	void GameState_TitleSingleton::Destroy()
	{
		if (0 != backgroundImage_) { destroy_bitmap(backgroundImage_); }
		if (0 != backgroundMusic_) { ENGINE::Audio::DestroyStream_OGG(backgroundMusic_); }
		if (0 != exitSound_) { destroy_sample(exitSound_); }
		if (0 != startSound_) { destroy_sample(startSound_); }
	}
	
	/**************************************************************************/
	// THERE IS NO NEED TO MODIFY THE METHODS BELOW THIS LINE!
	/**************************************************************************/
	
	GameState_TitleSingleton* GameState_TitleSingleton::GetInstance()
	{
		// return the singleton instance
		static GameState_TitleSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	GameState_TitleSingleton::GameState_TitleSingleton()
	{
		// implement class constructor here
		// DO NOT ALLOCATE MEMBER VARS IN THE CONSTRUCTOR!
		// USE THE Initialize METHOD ONLY!
	} // end constructor
	
	/**************************************************************************/
	
	GameState_TitleSingleton::~GameState_TitleSingleton()
	{
		// implement class destructor here
		Destroy();
	} // end destructor
	
	/**************************************************************************/
	
} // end namespace


