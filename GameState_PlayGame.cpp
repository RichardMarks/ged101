
// CODESTYLE: v2.0

// GameState_PlayGame.cpp
// Project: Game Engine Design 101 (GAME)
// Author: Richard Marks
// Purpose: The main game-play game state class.

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "GameState_PlayGame.h"

// include the game header
#include "Game.h"

// include the high precision timer header
#include "GameTimer.h"

// include the game state manager header
#include "GameStateManager.h"

// include the input manager header
#include "InputManager.h"

// include the error reporting header
#include "DebugReport.h"

// include the headers for each game state that you 
// will ever need to use from this state here
//#include "GameState_Paused.h"
//#include "GameState_InGameMenu.h"

namespace GAME
{
	/**
	* This is where you should initialize all your member variables.
	* This will be called after the engine is initialized, so you don't
	* have to worry about segfaults due to the engine libs not being init.
	*/
	void GameState_PlayGameSingleton::Initialize()
	{
		// make a call to our timer to get an initial time
		// note that we do not need to use the return value
		// for our first call, since the timer handles the time calculations.
		ENGINE::GameTimer;
		
		/*
		
		ENGINE::GameResource* music = ENGINE::GameResource::CreateAudioResource();
		music->Load("music.ogg");
		music->Play(true); // Play(bool playLooped = false);
		music->Stop();
		ENGINE::GameResource::DestroyAudioResource(music);
		
		
		ENGINE::AudioEngine->Initialize();
		unsigned int musicID = ENGINE::AudioEngine->Load("music.ogg");
		ENGINE::AudioEngine->Play(musicID, true);
		ENGINE::AudioEngine->Stop(musicID);
		ENGINE::AudioEngine->Destroy(musicID);
		
		
		*/
	}
	
	/**************************************************************************/
	
	/**
	* This is your place to implement the main logic of your state.
	* Don't forget to call the PopState method of the GameStateManager
	* when you are finished with this state, otherwise you will never
	* be able to exit the game!
	*/
	void GameState_PlayGameSingleton::Execute()
	{
		// define a color to be used later
		// we do this here to only have to make a call to makecol once
		// instead of every time the code loops.
		const int colorDarkBlue = makecol(0, 0, 48);
		
		// get a pointer to the back buffer surface for drawing on
		BITMAP* surface = GameInstance->GetBackBuffer();
		
		// our main logic loop
		bool finished = false;
		while(!finished)
		{
			// get the timing information from our timer
			float deltaTime = static_cast<float>(ENGINE::GameTimer->GetMilliseconds());
			
			// make sure we have the right data for the state of input devices.
			ENGINE::InputManager->Update();
			
			// if the user presses the escape key then exit the credits state
			if (ENGINE::InputManager->KeyPressed(KEY_ESC))
			{
				// leave this state
				ENGINE::GameStateManager->PopState();
				finished = true;
			}
			
			// update scene
			
			// clear the back buffer to a dark blue
			clear_to_color(surface, colorDarkBlue);
			
			// draw scene
			
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
	void GameState_PlayGameSingleton::Destroy()
	{
	}
	
	/**************************************************************************/
	// THERE IS NO NEED TO MODIFY THE METHODS BELOW THIS LINE!
	/**************************************************************************/
	
	GameState_PlayGameSingleton* GameState_PlayGameSingleton::GetInstance()
	{
		// return the singleton instance
		static GameState_PlayGameSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	GameState_PlayGameSingleton::GameState_PlayGameSingleton()
	{
		// implement class constructor here
		// DO NOT ALLOCATE MEMBER VARS IN THE CONSTRUCTOR!
		// USE THE Initialize METHOD ONLY!
	} // end constructor
	
	/**************************************************************************/
	
	GameState_PlayGameSingleton::~GameState_PlayGameSingleton()
	{
		// implement class destructor here
		Destroy();
	} // end destructor
	
	/**************************************************************************/
	
} // end namespace


