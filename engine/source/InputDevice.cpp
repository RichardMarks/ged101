
// CODESTYLE: v2.0

// InputDevice.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Implement the common interface for the input device class

/**
 * \file InputDevice.cpp
 * \brief Input Device Common Interface - Implementation
 */

// include the complementing header
#include "InputDevice.h"

namespace ENGINE
{
	InputDeviceSingleton* InputDeviceSingleton::GetInstance()
	{
		// return the singleton instance
		static InputDeviceSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	InputDeviceSingleton::InputDeviceSingleton() :
		joystickAvailable_(false)
	{
	}
	
	/**************************************************************************/
	
	InputDeviceSingleton::~InputDeviceSingleton()
	{
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::Initialize(unsigned int initMask)
	{
		// initialize each device if it has been asked to be initialized via the bitmask
		
		if (INIT_KEYBOARD & initMask)
		{
			InitializeKeyboard();
		}
		
		if (INIT_MOUSE & initMask)
		{
			InitializeMouse();
		}
		
		if (INIT_JOYSTICK & initMask)
		{
			InitializeJoystick();
		}
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::Update(unsigned int updateMask)
	{
		// update each device if it has been asked to be updated via the bitmask
		
		if (UPDATE_KEYBOARD & updateMask)
		{
			UpdateKeyboard();
		}
		
		if (UPDATE_MOUSE & updateMask)
		{
			UpdateMouse();
		}
		
		if (UPDATE_JOYSTICK & updateMask)
		{
			UpdateJoystick();
		}
	}
		
} // end namespace


