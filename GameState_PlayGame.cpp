
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
		
		
#if 1
		// create a player sprite
		ENGINE::GameSpriteManager->CreateSprite("player");
		
		// get a pointer to the player sprite
		ENGINE::GameSprite* playerSprite = ENGINE::GameSpriteManager->GetSprite("player");
		
		// create an animation sequence for when the player is idle
		playerSprite->CreateAnimationSequence("idle");
		
		// get a pointer to the idle animation sequence
		ENGINE::AnimationSequence* playerSpriteIdleAnimSeq = playerSprite->GetAnimationSequence("idle");
		
		// set the animation frames for the idle animation sequence
		playerSpriteIdleAnimSeq->SetFrames(
			ENGINE::AnimationFrame("playersheet.png",   0,   0,  31,  31),
			ENGINE::AnimationFrame("playersheet.png",  32,   0,  63,  31),
			ENGINE::AnimationFrame("playersheet.png",  64,   0,  95,  31));
		
		// set the animation sequence frame playback mode to alternate
		/*
			Playback Modes:
			
			ANIMATION_SEQ_PLAYBACK_ALTERNATE
			
				When the last frame is reached, the animation plays in reverse until
				the first frame is reached, and the the animation plays forwards again.
				This repeats indefinitely.
				
			ANIMATION_SEQ_PLAYBACK_REPEAT
			
				The animation starts back at the first frame when the last frame is reached.
				
			ANIMATION_SEQ_PLAYBACK_ALTERNATE_REVERSE
			
				Same as ANIMATION_SEQ_PLAYBACK_ALTERNATE except the animation starts on the
				last frame, and plays towards the first frame.
				
			ANIMATION_SEQ_PLAYBACK_REPEAT_REVERSE
			
				Same as ANIMATION_SEQ_PLAYBACK_REPEAT except the animation starts on the
				last frame, and plays towards the first frame.
				
			ANIMATION_SEQ_PLAYBACK_RANDOM
			
				A random frame is selected each time a frame change is required.
				
			ANIMATION_SEQ_PLAYBACK_CUSTOM
			
				You can specify a complicated arrangement of your frames by first
				setting this mode, and then calling SetCustomSequence() with an
				array of signed ints. Negative values correspond to the last frame
				plus one, minus the absolute value of the negative value.
				So -1 means the last frame.
		*/
		playerSpriteIdleAnimSeq->SetPlaybackMode(ENGINE::ANIMATION_SEQ_PLAYBACK_ALTERNATE);
		
		// set the delay times in milliseconds for each frame in the idle animation sequence
		playerSpriteIdleAnimSeq->SetGlobalDelay(500); // half a second should pass before frame changes
		
		
		
		
		// create a complex animation sequence
		
		// create an animation sequence for when the player is attacking with a sword
		playerSprite->CreateAnimationSequence("attack with sword");
		
		// get a pointer to the animation sequence
		ENGINE::AnimationSequence* playerSpriteSwordAttackAnimSeq = playerSprite->GetAnimationSequence("attack with sword");
		
		// We will place the rotation of the sword into its own sequence.
		ENGINE::AnimationSequence* sword360AnimSeq = new ENGINE::AnimationSequence();
		
		// set the delay times in milliseconds for each frame in the sword rotation animation sequence
		sword360AnimSeq->SetGlobalDelay(250); // a quarter second should pass before frame changes
		
		// set the animation sequence frame playback mode to repeat
		sword360AnimSeq->SetPlaybackMode(ENGINE::ANIMATION_SEQ_PLAYBACK_REPEAT);
		
		// load the image resource for the sword
		ENGINE::ImageResource* swordImage = new ENGINE::ImageResource();
		swordImage->LoadFrom("weaponsheet.png", 0, 0, 8, 16);
		
		// add the 8 rotation frames
		/*
			the sword is rotation 45 degrees each frame
			
			the position is relative to the anchor point
			
			-4 -3 -2 -1  0  1  2  3  4
			[ ][ ][ ][ ][1][ ][ ][ ][ ] -4
			[ ][ ][ ][ ][ ][ ][ ][ ][ ] -3
			[ ][ ][8][ ][ ][ ][2][ ][ ] -2
			[ ][ ][ ][ ][ ][ ][ ][ ][ ] -1
			[7][ ][ ][ ][X][ ][ ][ ][3]  0
			[ ][ ][ ][ ][ ][ ][ ][ ][ ]  1
			[ ][ ][6][ ][ ][ ][4][ ][ ]  2
			[ ][ ][ ][ ][ ][ ][ ][ ][ ]  3
			[ ][ ][ ][ ][5][ ][ ][ ][ ]  4
			
			The X is the anchor point, and the number 1 through 8 in the [ ] are the frames.
		*/
		
		// void AnimationSequence::AddNamedFrameEx(const char* name, ImageResource* image, int relativeX, int relativeY, int rotation);
		sword360AnimSeq->AddNamedFrameEx("sword n",  swordImage,   0,  -4,  0);
		sword360AnimSeq->AddNamedFrameEx("sword ne", swordImage,   2,  -2,  45);
		sword360AnimSeq->AddNamedFrameEx("sword e",  swordImage,   4,   0,  90);
		sword360AnimSeq->AddNamedFrameEx("sword se", swordImage,   2,   2,  135);
		sword360AnimSeq->AddNamedFrameEx("sword s",  swordImage,   0,   4,  180);
		sword360AnimSeq->AddNamedFrameEx("sword sw", swordImage,  -2,   2,  225);
		sword360AnimSeq->AddNamedFrameEx("sword w",  swordImage,  -4,   0,  270);
		sword360AnimSeq->AddNamedFrameEx("sword nw", swordImage,  -2,  -2,  315);
		
		// set the drawing anchor of the sword sequence
		playerSpriteSwordAttackAnimSeq->SetAnchorPoint(4, 14);
		
		// attach the sword animation sequence to the player's attack animation sequence 
		// to start at frame 1 of the parent animation
		playerSpriteSwordAttackAnimSeq->AddSequenceLayer("sword 360", sword360AnimSeq, 1);
		
		// set the animation frames for the player's attack animation sequence
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face n",  ENGINE::AnimationFrame("playersheet.png",   0,   31,  31,  63));
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face ne", ENGINE::AnimationFrame("playersheet.png",  32,   31,  63,  63));
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face e",  ENGINE::AnimationFrame("playersheet.png",  64,   31,  95,  63));
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face se", ENGINE::AnimationFrame("playersheet.png",  96,   31, 127,  63));
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face s",  ENGINE::AnimationFrame("playersheet.png", 128,   31, 159,  63));
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face sw", ENGINE::AnimationFrame("playersheet.png", 160,   31, 191,  63));
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face w",  ENGINE::AnimationFrame("playersheet.png", 192,   31, 223,  63));
		playerSpriteSwordAttackAnimSeq->AddNamedFrame("face nw", ENGINE::AnimationFrame("playersheet.png", 224,   31, 255,  63));
		
		// set the delay times in milliseconds for each frame in the player's attack animation sequence
		playerSpriteSwordAttackAnimSeq->SetGlobalDelay(250); // a quarter second should pass before frame changes
		
		// set the animation sequence frame playback mode to repeat
		playerSpriteSwordAttackAnimSeq->SetPlaybackMode(ENGINE::ANIMATION_SEQ_PLAYBACK_REPEAT);
		
		// set the drawing anchor point on the player sprite
		playerSprite->SetAnchorPoint(15, 28); // between the player's legs and just above the player's ankles
		
		// select the animation sequence we want to use
		playerSprite->SelectAnimationSequence("idle");
		
#endif
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


