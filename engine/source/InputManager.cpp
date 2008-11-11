
// CODESTYLE: v2.0

// GameState_PlayGame.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: This class wraps keyboard, mouse, and joystick functionality.

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "InputManager.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	InputManagerSingleton* InputManagerSingleton::GetInstance()
	{
		// return the singleton instance
		static InputManagerSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	InputManagerSingleton::InputManagerSingleton()
	{
		// implement class constructor here
		
	} // end constructor
	
	/**************************************************************************/
	
	InputManagerSingleton::~InputManagerSingleton()
	{
		// implement class destructor here
	} // end destructor
	
	/**************************************************************************/
	
	/**
	* You need to call this before you can use the other methods.
	*/
	void InputManagerSingleton::Initialize()
	{
		for (int index = 0; index < 255; index++)
		{
			keys_[index] = false;
			key_[index] = false;
		}
	}
	
	/**
	* Makes sure that the data on input devices is current
	*/
	void InputManagerSingleton::Update()
	{
		if (keyboard_needs_poll())
		{
			poll_keyboard();
		}
		
		for (int index = 0; index < 255; index++)
		{
			key_[index] = static_cast<bool>(key[index]);
		}
	}
		
	/**************************************************************************/
	
	bool InputManagerSingleton::KeyPressed(int keyCode)
	{
		/** 
		* Thanks to mokkan in #allegro on irc.freenode.net for this.
		* Handle key presses without the annoying repeating crap!
		*/
		if (key[keyCode] && !keys_[keyCode])
		{
			keys_[keyCode] = true;
			return true;
		}
		else if (!key[keyCode])
		{
			keys_[keyCode] = false;
		}
		return false;
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::KeyDown(int keyCode)
	{
		return key_[keyCode];
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::KeyUp(int keyCode)
	{
		return !key_[keyCode];
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::KeyPressed(int modifier, int keyCode)
	{
		return static_cast<bool>((key_shifts & modifier) && KeyPressed(keyCode));
	}
	
	bool InputManagerSingleton::KeyDown(int modifier, int keyCode)
	{
		return static_cast<bool>((key_shifts & modifier) && KeyDown(keyCode));
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::KeyUp(int modifier, int keyCode)
	{
		return static_cast<bool>((key_shifts & modifier) && KeyUp(keyCode));
	}
	
} // end namespace


