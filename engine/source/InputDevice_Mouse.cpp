
// CODESTYLE: v2.0

// InputDevice_Mouse.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Implement the interface to the mouse input device

/**
 * \file InputDevice_Mouse.cpp
 * \brief Mouse Input Device Interface Module - Implementation
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "InputDevice.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	void InputDeviceSingleton::InitializeMouse()
	{
		static bool firstCall = true;
		
		// make sure that we only install the mouse driver once
		// because this routine possibly may be called multiple times
		if (firstCall)
		{
			// install the Allegro mouse driver
			if (install_mouse() < 0)
			{
				LogFatal("Could not install Allegro Mouse driver!");
			}
			
			// first-time-only initialize has finished
			firstCall = false;
		}
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::UpdateMouse()
	{
		if (mouse_needs_poll())
		{
			poll_mouse();
		}
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::MouseButtonDown(int button)
	{
		return static_cast<bool>(mouse_b & button);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::MouseButtonUp(int button)
	{
		return static_cast<bool>(!(mouse_b & button));
	}
	
	/**************************************************************************/
	
	int InputDeviceSingleton::MouseX()
	{
		return mouse_x;
	}
	
	/**************************************************************************/
	
	int InputDeviceSingleton::MouseY()
	{
		return mouse_y;
	}
	
	/**************************************************************************/
	
	int InputDeviceSingleton::MouseZ()
	{
		return mouse_z;
	}
	
	/**************************************************************************/
	
	int InputDeviceSingleton::MouseMoveRelative(AXIS::Axis axis)
	{
		int x = 0, y = 0;
		get_mouse_mickeys(&x, &y);
		
		if (AXIS::Axis_X == axis)
		{
			return x;
		}
		else if (AXIS::Axis_Y == axis)
		{
			return y;
		}
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::MouseSetPosition(int x, int y, int z)
	{
		position_mouse(x, y);
		position_mouse_z(z);
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::MouseSetRegion(int left, int top, int right, int bottom)
	{
		set_mouse_range(left, top, right, bottom);
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::MouseSetSpeed(int speedX, int speedY)
	{
		set_mouse_speed(speedX, speedY);
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::MouseSetCursorImage(ImageResource* image, int hotSpotX, int hotSpotY)
	{
		set_mouse_sprite((0 != image) ? image->GetBitmap() : 0);
		set_mouse_sprite_focus(hotSpotX, hotSpotY);
	}
	
} // end namespace
