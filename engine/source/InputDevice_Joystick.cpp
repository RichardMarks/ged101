
// CODESTYLE: v2.0

// InputDevice_Joystick.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Implement the interface to the joystick input device

/**
 * \file InputDevice_Joystick.cpp
 * \brief Joystick Input Device Interface Module - Implementation
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

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	void InputDeviceSingleton::InitializeJoystick()
	{
		static bool firstCall = true;
		
		// make sure that we only install the joystick driver once
		// because this routine may incorrectly be called multiple times
		if (firstCall)
		{
			/*
			 * check to see if the joysticks have previously been calibrated
			 *
			 * if the joysticks were not calibrated, then we go through a
			 * calibration sequence and then save the calibration data to a file.
			 *
			 * if the calibration file exists, we then try to load the data.
			 * if the loading of the data fails, then we disable the joystick.
			 */
			bool previouslyCalibrated = false;
			
			FILE* fp = fopen("joysettings.dat", "rb"); 
			
			if (fp) 
			{
				fclose(fp); 
				if (0 != load_joystick_data("joysettings.dat"))
				{
					LogWarning("Joystick Data File was found, but it could not be loaded! Possibly has been corrupted!");
				}
				else
				{
					previouslyCalibrated = true;
					joystickAvailable_ = true;
				}
			}
			
			if (!previouslyCalibrated)
			{
				// try to install the joystick driver
				if (0 != install_joystick(JOY_TYPE_AUTODETECT))
				{
					LogFatal("Could not install Allegro Joystick driver!");
				}
				
				// calibrate the joysticks
				BeginJoystickCalibration();
			}
			
			// first-time-only initialize has finished
			firstCall = false;
		}
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::UpdateJoystick()
	{
		poll_joystick();
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyExists(int joystick)
	{
		return static_cast<bool>(joystick < num_joysticks);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyButtonExists(int joystick, int button)
	{
		return static_cast<bool>(InputDeviceSingleton::JoyExists(joystick) && button < joy[joystick].num_buttons);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyStickExists(int joystick, int stick)
	{
		return static_cast<bool>(InputDeviceSingleton::JoyExists(joystick) && stick < joy[joystick].num_sticks);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyButtonDown(int button, int joystick)
	{
		return static_cast<bool>(InputDeviceSingleton::JoyButtonExists(joystick, button) && joy[joystick].button[button].b);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyButtonUp(int button, int joystick)
	{
		return static_cast<bool>(!(InputDeviceSingleton::GetInstance()->JoyButtonDown(joystick, button)));
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyUp(int joystick, int stick)
	{
		return static_cast<bool>(InputDeviceSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[1].d1);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyDown(int joystick, int stick)
	{
		return static_cast<bool>(InputDeviceSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[1].d2);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyLeft(int joystick, int stick)
	{
		return static_cast<bool>(InputDeviceSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[0].d1);
	}
	
	/**************************************************************************/
	
	bool InputDeviceSingleton::JoyRight(int joystick, int stick)
	{
		return static_cast<bool>(InputDeviceSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[0].d2);
	}
	
	/**************************************************************************/
	
	int InputDeviceSingleton::Joy(AXIS::Axis axis, int stick, int joystick)
	{
		// cast the axis into an integer we need to index into things
		int a = static_cast<int>(axis);
		
		if (InputDeviceSingleton::JoyStickExists(joystick, stick))
		{
			if (a < joy[joystick].stick[stick].num_axis)
			{
				return static_cast<int>(joy[joystick].stick[stick].axis[a].pos);
			}
		}
		return 0;
	}
	
	/**************************************************************************/
	
	void InputDeviceSingleton::BeginJoystickCalibration()
	{
		int msgColor 	= makecol(255, 255, 255);
		int bgColor		= makecol(0, 0, 255);
		
		// for each joystick, run a calibration sequence
		for (int index = 0; index < num_joysticks; index++)
		{
			// clear the screen
			clear_to_color(screen, bgColor);
			
			// while the jostick needs to be calibrated
			while (joy[index].flags & JOYFLAG_CALIBRATE) 
			{
				// get the calibration message
				const char* message = calibrate_joystick_name(index);
				
				// show the message on the screen
				textprintf_centre_ex(screen, 
					font, SCREEN_W / 2, SCREEN_H / 2, 
					msgColor, 
					-1, 
					"%s, and press a key.", 
					message); 
				
				// read a key
				readkey();
				
				// try to calibrate the joystick
				if (0 != calibrate_joystick(index)) 
				{
					// show a message that we failed
					textprintf_centre_ex(screen, 
						font, SCREEN_W / 2, 64 + (SCREEN_H / 2), 
						msgColor, 
						-1, 
						"Could not calibrate the Joystick!");
					
					// read a key
					readkey();
					
					// and bail with a fatal error
					LogFatal("Could not calibrate the joystick!");
				}
			}
		}
		
		// try to save the calibration data to a file
		if (0 != save_joystick_data("joysettings.dat"))
		{
			// clear the screen to red
			clear_to_color(screen, makecol(255, 0, 0));
		
			// show a message on the screen
			textprintf_centre_ex(screen, 
				font, SCREEN_W / 2, SCREEN_H / 2, 
				makecol(255, 255, 0), 
				-1, 
				"Joystick Calibration data file could not be saved! Press a key to exit the program.");
		
			// read a key
			readkey();
			LogFatal("Joystick Calibration data file could not be saved! Program will now exit!");
		}
		
		// clear the screen
		clear_to_color(screen, bgColor);
		
		// show a message on the screen
		textprintf_centre_ex(screen, 
			font, SCREEN_W / 2, SCREEN_H / 2, 
			msgColor, 
			-1, 
			"Joysticks have been calibrated. Press a key to exit the program.");
		
		// read a key
		readkey();
		
		// log a message that the joysticks were calibrated
		LogMessage("Joysticks calibrated! Program Exiting...");
		exit(1);
	}
	
} // end namespace
