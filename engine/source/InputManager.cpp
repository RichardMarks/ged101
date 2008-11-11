
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

// include the image header
#include "Image.h"

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
		joystickAvailable_ = false;
	} // end constructor
	
	/**************************************************************************/
	
	InputManagerSingleton::~InputManagerSingleton()
	{
		// implement class destructor here
	} // end destructor
	
	/**************************************************************************/
	
	/**
	* Installs the Allegro input device drivers on the first call.
	* You need to call this before you can use the other methods.
	*/
	void InputManagerSingleton::Initialize()
	{
		static bool firstCall = true;
		
		// make sure that we only install the keyboard driver once
		// because this routine may incorrectly be called multiple times
		if (firstCall)
		{
			// install the Allegro keyboard driver
			if (0 != install_keyboard())
			{
				LogFatal("Could not install Allegro Keyboard driver!");
			}
			
			// install the Allegro mouse driver
			if (install_mouse() < 0)
			{
				LogFatal("Could not install Allegro Mouse driver!");
			}
			
			
			/**
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
		
		// reset the keyboard boolean arrays
		for (int index = 0; index < 255; index++)
		{
			keys_[index] = false;
			key_[index] = false;
		}
	}
	
	/**
	* Joystick Calibration Sequence
	*
	* After the sequence has finished, the program is closed down.
	*/
	void InputManagerSingleton::BeginJoystickCalibration()
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
	
	/**************************************************************************/
	
	bool InputManagerSingleton::MouseButtonDown(int button)
	{
		return static_cast<bool>(mouse_b & button);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::MouseButtonUp(int button)
	{
		return static_cast<bool>(!(mouse_b & button));
	}
	
	/**************************************************************************/
	
	int InputManagerSingleton::MouseX()
	{
		return mouse_x;
	}
	
	/**************************************************************************/
	
	int InputManagerSingleton::MouseY()
	{
		return mouse_y;
	}
	
	/**************************************************************************/
	
	int InputManagerSingleton::MouseZ()
	{
		return mouse_z;
	}
	
	/**************************************************************************/
	
	int InputManagerSingleton::MouseMoveRelative(int axis)
	{
		int x = 0, y = 0;
		get_mouse_mickeys(&x, &y);
		
		if (axis == 1)
		{
			return x;
		}
		else if (axis == 2)
		{
			return y;
		}
	}
	
	/**************************************************************************/
	
	void InputManagerSingleton::MouseSetPosition(int x, int y, int z)
	{
		position_mouse(x, y);
		position_mouse_z(z);
	}
	
	/**************************************************************************/
	
	void InputManagerSingleton::MouseSetRegion(int left, int top, int right, int bottom)
	{
		set_mouse_range(left, top, right, bottom);
	}
	
	/**************************************************************************/
	
	void InputManagerSingleton::MouseSetSpeed(int speedX, int speedY)
	{
		set_mouse_speed(speedX, speedY);
	}
	
	/**************************************************************************/
	
	void InputManagerSingleton::MouseSetCursorImage(ImageResource* image, int hotSpotX, int hotSpotY)
	{
		set_mouse_sprite((0 != image) ? image->GetBitmap() : 0);
		set_mouse_sprite_focus(hotSpotX, hotSpotY);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyExists(int joystick)
	{
		return static_cast<bool>(joystick < num_joysticks);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyButtonExists(int joystick, int button)
	{
		return static_cast<bool>(InputManagerSingleton::JoyExists(joystick) && button < joy[joystick].num_buttons);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyStickExists(int joystick, int stick)
	{
		return static_cast<bool>(InputManagerSingleton::JoyExists(joystick) && stick < joy[joystick].num_sticks);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyButtonDown(int button, int joystick)
	{
		return static_cast<bool>(InputManagerSingleton::JoyButtonExists(joystick, button) && joy[joystick].button[button].b);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyButtonUp(int button, int joystick)
	{
		return static_cast<bool>(!(InputManagerSingleton::GetInstance()->JoyButtonDown(joystick, button)));
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyUp(int joystick, int stick)
	{
		return static_cast<bool>(InputManagerSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[1].d1);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyDown(int joystick, int stick)
	{
		return static_cast<bool>(InputManagerSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[1].d2);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyLeft(int joystick, int stick)
	{
		return static_cast<bool>(InputManagerSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[0].d1);
	}
	
	/**************************************************************************/
	
	bool InputManagerSingleton::JoyRight(int joystick, int stick)
	{
		return static_cast<bool>(InputManagerSingleton::JoyStickExists(joystick, stick) && joy[joystick].stick[stick].axis[0].d2);
	}
	
	/**************************************************************************/
	
	int InputManagerSingleton::Joy(int axis, int stick, int joystick)
	{
		if (InputManagerSingleton::JoyStickExists(joystick, stick))
		{
			if (axis < joy[joystick].stick[stick].num_axis)
			{
				return static_cast<int>(joy[joystick].stick[stick].axis[axis].pos);
			}
		}
		return 0;
	}
	
} // end namespace


