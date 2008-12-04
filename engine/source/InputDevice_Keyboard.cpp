
// CODESTYLE: v2.0

// InputDevice_Keyboard.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Implement the interface to the keyboard input device

/**
 * \file InputDevice_Keyboard.cpp
 * \brief Keyboard Input Device Interface Module - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "InputDevice.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	void InputDeviceSingleton::InitializeKeyboard()
	{
		static bool firstCall = true;
		
		// make sure that we only install the keyboard driver once
		// because this routine possibly may be called multiple times
		if (firstCall)
		{
			// install the Allegro keyboard driver
			if (0 != install_keyboard())
			{
				LogFatal("Could not install Allegro Keyboard driver!");
			}
			
			// first-time-only initialize has finished
			firstCall = false;
		}
		
		// reset the keyboard boolean arrays
		for (int index = 0; index < 255; index++)
		{
			keys_[index] = false;
			key_[index] = false;
		}
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::UpdateKeyboard()
	{
		if (keyboard_needs_poll())
		{
			poll_keyboard();
		}
		
		for (int index = 0; index < KEY::Key_Max; index++)
		{
			key_[index] = static_cast<bool>(key[index]);
		}
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::KeyPressed(KEY::VirtualKey keyCode)
	{
		// cast the virtual key into an int we can use to index into the Allegro key array
		int k = static_cast<int>(keyCode);
		
		// Thanks to mokkan in #allegro on irc.freenode.net for this.
		// Handle key presses without the annoying repeating crap!
		
		// if the key is current down, and was not previously down
		if (key[k] && !keys_[k])
		{
			// the key was pressed, set the flag
			keys_[k] = true;
			return true;
		}
		// if the key is not currently down
		else if (!key[k])
		{
			// unset the flag
			keys_[k] = false;
		}
		
		return false;
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::KeyDown(KEY::VirtualKey keyCode)
	{
		// cast the virtual key into an int we can use to index into the key_ array
		return key_[static_cast<int>(keyCode)];
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::KeyUp(KEY::VirtualKey keyCode)
	{
		// cast the virtual key into an int we can use to index into the key_ array
		return !key_[static_cast<int>(keyCode)];
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::KeyPressed(KEY::Modifier modifier, KEY::VirtualKey keyCode)
	{
		// cast the key modifier into an int we can use to check the bitmask on
		int m = static_cast<int>(modifier);
		
		return static_cast<bool>((key_shifts & m) && KeyPressed(keyCode));
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::KeyDown(KEY::Modifier modifier, KEY::VirtualKey keyCode)
	{
		// cast the key modifier into an int we can use to check the bitmask on
		int m = static_cast<int>(modifier);
		
		return static_cast<bool>((key_shifts & m) && KeyDown(keyCode));
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::KeyUp(KEY::Modifier modifier, KEY::VirtualKey keyCode)
	{
		// cast the key modifier into an int we can use to check the bitmask on
		int m = static_cast<int>(modifier);
		
		return static_cast<bool>((key_shifts & m) && KeyUp(keyCode));
	}
	
} // end namespace
