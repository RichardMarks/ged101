
// CODESTYLE: v2.0

// InputDevice.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Interface to the input devices; keyboard, mouse, and joystick

/**
 * \file InputDevice.h
 * \brief Input Device Interface Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __INPUTDEVICE_H__
#define __INPUTDEVICE_H__

namespace ENGINE
{
	// forward declare classes we need
	class ImageResource;
	
	/**
	 * \namespace ENGINE::KEY
	 * \brief key enumerations for the keyboard interface module
	 */
	namespace KEY
	{
		/**
		 * \enum KEY::Modifier
		 * \brief modifier key bit masks to be used in the keyboard functions to check modifier keys such as CTRL
		 */
		enum Modifier
		{
			Mod_Shift		= 0x0001,
			Mod_Ctrl		= 0x0002,
			Mod_Alt			= 0x0004,
			Mod_LSuper		= 0x0008,
			Mod_RSuper		= 0x0010,
			Mod_Menu		= 0x0020,
			Mod_Command		= 0x0040,
			Mod_ScrollLock	= 0x0100,
			Mod_NumLock		= 0x0200,
			Mod_CapsLock	= 0x0400,
			Mod_InAltSeq	= 0x0800,
			Mod_Accent1		= 0x1000,
			Mod_Accent2		= 0x2000,
			Mod_Accent3		= 0x4000,
			Mod_Accent4		= 0x8000
		};
	
		/**
		 * \enum KEY::VirtualKey
		 * \brief virtual-key codes for every key we could ever need
		 */
		enum VirtualKey
		{
			Key_A			= 0x1,
			Key_B			= 0x2,
			Key_C			= 0x3,
			Key_D			= 0x4,
			Key_E			= 0x5,
			Key_F			= 0x6,
			Key_G			= 0x7,
			Key_H			= 0x8,
			Key_I			= 0x9,
			Key_J			= 0xA,
			Key_K			= 0xB,
			Key_L			= 0xC,
			Key_M			= 0xD,
			Key_N			= 0xE,
			Key_O			= 0xF,
			Key_P			= 0x10,
			Key_Q			= 0x11,
			Key_R			= 0x12,
			Key_S			= 0x13,
			Key_T			= 0x14,
			Key_U			= 0x15,
			Key_V			= 0x16,
			Key_W			= 0x17,
			Key_X			= 0x18,
			Key_Y			= 0x19,
			Key_Z			= 0x1A,
			Key_0			= 0x1B,
			Key_1			= 0x1C,
			Key_2			= 0x1D,
			Key_3			= 0x1E,
			Key_4			= 0x1F,
			Key_5			= 0x20,
			Key_6			= 0x21,
			Key_7			= 0x22,
			Key_8			= 0x23,
			Key_9			= 0x24,
			Key_Num0		= 0x25,
			Key_Num1		= 0x26,
			Key_Num2		= 0x27,
			Key_Num3		= 0x28,
			Key_Num4		= 0x29,
			Key_Num5		= 0x2A,
			Key_Num6		= 0x2B,
			Key_Num7		= 0x2C,
			Key_Num8		= 0x2D,
			Key_Num9		= 0x2E,
			Key_F1			= 0x2F,
			Key_F2			= 0x30,
			Key_F3			= 0x31,
			Key_F4			= 0x32,
			Key_F5			= 0x33,
			Key_F6			= 0x34,
			Key_F7			= 0x35,
			Key_F8			= 0x36,
			Key_F9			= 0x37,
			Key_F10			= 0x38,
			Key_F11			= 0x39,
			Key_F12			= 0x3A,
			Key_Escape		= 0x3B,
			Key_Tilde		= 0x3C,
			Key_Minus		= 0x3D,
			Key_Equals		= 0x3E,
			Key_Backspace	= 0x3F,
			Key_Tab			= 0x40,
			Key_OpenBrace	= 0x41,
			Key_CloseBrace	= 0x42,
			Key_Enter		= 0x43,
			Key_Colon		= 0x44,
			Key_Quote		= 0x45,
			Key_Backslash	= 0x46,
			Key_Backslash2	= 0x47,
			Key_Comma		= 0x48,
			Key_Stop		= 0x49,
			Key_Divide		= 0x4A,
			Key_Space		= 0x4B,
			Key_Insert		= 0x4C,
			Key_Delete		= 0x4D,
			Key_Home		= 0x4E,
			Key_End			= 0x4F,
			Key_PageUp		= 0x50,
			Key_PageDown	= 0x51,
			Key_Left		= 0x52,
			Key_Right		= 0x53,
			Key_Up			= 0x54,
			Key_Down		= 0x55,
			Key_NumDivide	= 0x56,
			Key_Asterisk	= 0x57,
			Key_NumMinus	= 0x58,
			Key_NumPlus		= 0x59,
			Key_NumDelete	= 0x5A,
			Key_NumEnter	= 0x5B,
			Key_PrintScreen = 0x5C,
			Key_Pause		= 0x5D,
			Key_AbntC1		= 0x5E,
			Key_Yen			= 0x5F,
			Key_Kana		= 0x60,
			Key_Convert		= 0x61,
			Key_NoConvert	= 0x62,
			Key_At			= 0x63,
			Key_Circumflex	= 0x64,
			Key_Colon2		= 0x65,
			Key_Kanji		= 0x66,
			Key_NumEquals	= 0x67,
			Key_Backtick	= 0x68,
			Key_Semicolon	= 0x69,
			Key_Command		= 0x6A,
			Key_Unknown1	= 0x6B,
			Key_Unknown2	= 0x6C,
			Key_Unknown3	= 0x6D,
			Key_Unknown4	= 0x6E,
			Key_Unknown5	= 0x6F,
			Key_Unknown6	= 0x70,
			Key_Unknown7	= 0x71,
			Key_Unknown8	= 0x72,
			Key_Modifiers	= 0x73,
			Key_LShift		= 0x73,
			Key_RShift		= 0x74,
			Key_LCtrl		= 0x75,
			Key_RCtrl		= 0x76,
			Key_Alt			= 0x77,
			Key_AltGr		= 0x78,
			Key_LSuper		= 0x79,
			Key_RSuper		= 0x7A,
			Key_Menu		= 0x7B,
			Key_ScrollLock	= 0x7C,
			Key_NumLock		= 0x7D,
			Key_CapsLock	= 0x7E,
			Key_Max			= 0x7F		
		};
		
	} // end namespace
	
	/**
	 * \namespace ENGINE::AXIS
	 * \brief enumerations for devices that move on any of 3 cardinal axes
	 */
	namespace AXIS
	{
		/**
		 * \enum AXIS::Axis
		 * \brief enumerations for devices that move on any of 3 cardinal axes
		 */
		enum Axis
		{
			Axis_X = 0x1,
			Axis_Y = 0x2,
			Axis_Z = 0x3
		};
	} // end namespace
	
	//! bitmask for the InputDeviceSingleton::Initialize() function. -- initialize the keyboard
	const unsigned int INIT_KEYBOARD 		= 0x0001;
	
	//! bitmask for the InputDeviceSingleton::Initialize() function -- initialize the mouse
	const unsigned int INIT_MOUSE			= 0x0002;
	
	//! bitmask for the InputDeviceSingleton::Initialize() function -- initialize the joystick
	const unsigned int INIT_JOYSTICK		= 0x0004;
	
	//! bitmask for the InputDeviceSingleton::Initialize() function -- initialize all devices
	const unsigned int INIT_ALLDEVICES 		= 0x0007;
	
	//! bitmask for the InputDeviceSingleton::Update() function. -- update the keyboard
	const unsigned int UPDATE_KEYBOARD 		= 0x0001;
	
	//! bitmask for the InputDeviceSingleton::Update() function -- update the mouse
	const unsigned int UPDATE_MOUSE			= 0x0002;
	
	//! bitmask for the InputDeviceSingleton::Update() function -- update the joystick
	const unsigned int UPDATE_JOYSTICK		= 0x0004;
	
	//! bitmask for the InputDeviceSingleton::Update() function -- update all devices
	const unsigned int UPDATE_ALLDEVICES 	= 0x0007;
	
	/**
	 * \class InputDeviceSingleton
	 * \brief Interface to the input devices; keyboard, mouse, and joystick
	 * \ingroup InputGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class InputDeviceSingleton
	{
	public:
		
		/**
		 * \return a pointer to the input device singleton
		 */
		static InputDeviceSingleton* GetInstance();
		
		/**
		 * default destructor - De-allocates any allocated memory
		 */
		~InputDeviceSingleton();
		
		/**
		 * Installs the input device drivers on the first call.
		 * You need to call this at least once before you can use the other methods.
		 * @param initMask is a bitmask to say what devices to initialize. possible values are INIT_KEYBOARD, INIT_MOUSE, INIT_JOYSTICK, INIT_ALLDEVICES
		 */
		void Initialize(unsigned int initMask = INIT_ALLDEVICES);
		
		/**
		 * Updates all input devices so that the device data is current
		 * If you do not pass a parameter, then all devices will be updated.
		 * @param updateMask is a bitmask to say what devices to update. possible values are UPDATE_KEYBOARD, UPDATE_MOUSE, UPDATE_JOYSTICK, UPDATE_ALLDEVICES
		 */
		void Update(unsigned int updateMask = UPDATE_ALLDEVICES);
		
		////////////////////////////////////////////////////////////////////////
		//                  END OF COMMON INTERFACE
		////////////////////////////////////////////////////////////////////////
		
		
		
		// keyboard functionality
		
		/**
		 * Checks for a key being pressed in a non-repeating manner.
		 * @param keyCode is the virtual-key code constant such as KEY::Key_Escape to check
		 * /return true if the key was presssed, false if not
		 */
		bool KeyPressed(KEY::VirtualKey keyCode);
		
		/**
		 * Checks that a key is currently being pressed down in a repeating manner.
		 * @param keyCode is the virtual-key code constant such as KEY::Key_Left to check
		 * \return true if the key is currently down, and false if not
		 */
		bool KeyDown(KEY::VirtualKey keyCode);
		
		/**
		 * Checks that a key is currently not being pressed down in a repeating manner.
		 * @param keyCode is the virtual-key code constant such as KEY::Key_Left to check
		 * \return true if the key is currently up, and false if it is down
		 */
		bool KeyUp(KEY::VirtualKey keyCode);
		
		/**
		 * Checks for a key being pressed in a non-repeating manner.
		 * Also checks for a modifier such as KEY::Mod_Ctrl
		 * @param modifier is a key modifier bit mask such as KEY::Mod_Ctrl
		 * @param keyCode is the virtual-key code constant such as KEY::Key_Escape to check
		 * /return true if the key was presssed, false if not
		 */
		bool KeyPressed(KEY::Modifier modifier, KEY::VirtualKey keyCode);
		
		/**
		 * Checks that a key is currently being pressed down in a repeating manner.
		 * @param modifier is a key modifier bit mask such as KEY::Mod_Ctrl
		 * @param keyCode is the virtual-key code constant such as KEY::Key_Left to check
		 * \return true if the key is currently down, and false if not
		 */
		bool KeyDown(KEY::Modifier modifier, KEY::VirtualKey keyCode);
		
		/**
		 * Checks that a key is currently not being pressed down in a repeating manner.
		 * @param modifier is a key modifier bit mask such as KEY::Mod_Ctrl
		 * @param keyCode is the virtual-key code constant such as KEY::Key_Left to check
		 * \return true if the key is currently up, and false if it is down
		 */
		bool KeyUp(KEY::Modifier modifier, KEY::VirtualKey keyCode);
		
		////////////////////////////////////////////////////////////////////////
		//                  END OF KEYBOARD INTERFACE
		////////////////////////////////////////////////////////////////////////
		
		// mouse functionality
		
		/**
		 * Checks to see if the button is currently down
		 * \returns true if the button is down, false if not
		 */
		bool MouseButtonDown(int button);
		/**
		 * Checks to see if the button is currently up
		 * \returns true if the button is up, false if not
		 */
		bool MouseButtonUp(int button);
		
		/**
		 * \return the X pixel coordinate of the mouse pointer
		 */
		int MouseX();
		
		/**
		 * \return the Y pixel coordinate of the mouse pointer
		 */
		int MouseY();
		
		/**
		 * \return the mouse wheel position
		 */
		int MouseZ();
		
		/**
		 * Measures how far the mouse has moved on a given axis since the last call to this function. 
		 * The returned values will become negative if the mouse is moved left or up.
		 * The mouse will continue to generate movement mickeys even when it reaches the edge of the screen, 
		 * so this form of input can be useful for games that require an infinite range of mouse movement.
		 * @param axis is which axis to check. AXIS::Axis_X checks the horizontal motion, AXIS::Axis_Y checks the vertical motion.
		 * \return the amount of pixels the mouse has moved on a given axis, relative to the last time the function was called
		 */
		int MouseMoveRelative(AXIS::Axis axis);
		
		/**
		 * Sets the position of the mouse and optionally the mouse wheel.
		 * @param x is the new horizontal mouse position in pixels.
		 * @param y is the new vertical mouse position in pixels.
		 * @param z is the new mouse wheel position.
		 */
		void MouseSetPosition(int x, int y, int z = 0);
		
		/**
		 * Sets the area of the screen within which the mouse can move. Pass the top left corner and the bottom right corner (inclusive)
		 * @param left is the X coordinate of the upper-left corner in pixels.
		 * @param top is the Y coordinate of the upper-left corner in pixels.
		 * @param right is the X coordinate of the lower-right corner in pixels.
		 * @param bottom is the Y coordinate of the lower-right corner in pixels.
		 */
		void MouseSetRegion(int left, int top, int right, int bottom);
		
		/**
		 * Sets the speed of the mouse cursor.
		 * Larger values of \a speedX and \a speedY represent slower mouse movement. The default for both is 2.
		 * @param speedX is the horizontal speed of the mouse.
		 * @param speedY is the vertical speed of the mouse.
		 */
		void MouseSetSpeed(int speedX = 2, int speedY = 2);
		
		/**
		 * Changes the image of the mouse cursor.
		 * You can optionally change the hot-spot of the mouse cursor.\n
		 * This "clicky" point is the location on the mouse cursor that determines the position of the mouse cursor.\n
		 * By default, this is the upper-left corner of the cursor at 0, 0.
		 * @param image is an ImageResource containing the image to use for the mouse cursor.
		 * @param hotSpotX is the X coordinate of the actual "clicky" point of the mouse cursor in pixels.
		 * @param hotSpotY is the Y coordinate of the actual "clicky" point of the mouse cursor in pixels.
		 */
		void MouseSetCursorImage(ImageResource* image = 0, int hotSpotX = 0, int hotSpotY = 0);
		
		////////////////////////////////////////////////////////////////////////
		//                  END OF MOUSE INTERFACE
		////////////////////////////////////////////////////////////////////////
		
		// joystick functionality
		
		/**
		 * A mini-program in its own right, this function calibrates the joysticks attached to the
		 * computer, and saves the calibration data to a file.
		 * The program will exit to the OS after the calibration is complete.
		 */
		void BeginJoystickCalibration();
		
		/**
		 * Validate a joystick by ID
		 * @param joystick is an integer to specify the ID # of the joystick. 0 is the default
		 * \return true if the passed joystickID is valid.
		 */
		static bool JoyExists(int joystick = 0);
		
		/**
		 * Validate a joystick button by ID
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * @param button is an integer to specify the ID # of the joystick button.
		 * \return true if the passed buttonID is valid.
		 */
		static bool JoyButtonExists(int joystick, int button);
		
		/**
		 * Validate a joystick stick (the actual thing you hold on to) by ID
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * @param stick is an integer to specify the ID # of the joystick stick.
		 * \return true if the passed stickID is valid.
		 */
		static bool JoyStickExists(int joystick, int stick);
		
		// digital joystick input
		
		/**
		 * Checks if a button on the joystick is currently down.
		 * @param button is an integer to specify the ID # of the joystick button.
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * \return true if the button is down.
		 */
		bool JoyButtonDown(int button, int joystick = 0);
		
		/**
		 * Checks if a button on the joystick is currently up.
		 * @param button is an integer to specify the ID # of the joystick button.
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * \return true if the button is up.
		 */
		bool JoyButtonUp(int button, int joystick = 0);
		
		/**
		 * Check if joystick is pushed up (on a game pad) or forward (on a flight stick)
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * @param stick is an integer to specify the ID # of the joystick stick.
		 * \return true if the joystick stick is pushed up (on a game pad) or forward (on a flight stick)
		 */
		bool JoyUp(int joystick = 0, int stick = 0);
		
		/**
		 * Check if joystick is pushed down (on a game pad) or back (on a flight stick)
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * @param stick is an integer to specify the ID # of the joystick stick.
		 * \return true if the joystick stick is pushed down (on a game pad) or back (on a flight stick)
		 */
		bool JoyDown(int joystick = 0, int stick = 0);
		
		/**
		 * Check if joystick is pushed left (on a game pad or on a flight stick)
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * @param stick is an integer to specify the ID # of the joystick stick.
		 * \return true if the joystick stick is pushed left (on a game pad or on a flight stick)
		 */
		bool JoyLeft(int joystick = 0, int stick = 0);
		
		/**
		 * Check if joystick is pushed right (on a game pad or on a flight stick)
		 * @param joystick is an integer to specify the ID # of the joystick.
		 * @param stick is an integer to specify the ID # of the joystick stick.
		 * \return true if the joystick stick is pushed right (on a game pad or on a flight stick)
		 */
		bool JoyRight(int joystick = 0, int stick = 0);
		
		// analogue joystick input
		
		/**
		 * Get analogue joystick input (relative motion of the joystick on a given axis)
		 * @param axis is the axis to check motion on. Possible values are AXIS::Axis_X, AXIS::Axis_Y, AXIS::Axis_Z.
		 * @param stick is the stickID to check. Default is 0
		 * @param joystick is the joystickID to check. Default is 0
		 * \return the relative position of the joystick motion on a given axis.
		 */
		int Joy(AXIS::Axis axis, int stick = 0, int joystick = 0);
		
		////////////////////////////////////////////////////////////////////////
		//                  END OF JOYSTICK INTERFACE
		////////////////////////////////////////////////////////////////////////
		
	private:
		// private members should be declared here
		
		/**
		 * The keyboard input device initialization function
		 */
		void InitializeKeyboard();
		
		/**
		 * The mouse input device initialization function
		 */
		void InitializeMouse();
		
		/**
		 * The joystick input device initialization function
		 */
		void InitializeJoystick();
		
		/**
		 * The keyboard input device update function
		 */
		void UpdateKeyboard();
		
		/**
		 * The mouse input device update function
		 */
		void UpdateMouse();
		
		/**
		 * The joystick input device update function
		 */
		void UpdateJoystick();
		
		/**
		 * The class constructor is hidden because this is a singleton.
		 */
		InputDeviceSingleton();
		
		/**
		 * The copy constructor is hidden because the class cannot be copied.
		 */
		InputDeviceSingleton(const InputDeviceSingleton& rhs);
		
		/**
		 * The assignment operator is hidden because the class cannot be copied.
		 */
		InputDeviceSingleton& operator=(const InputDeviceSingleton& rhs);
		
		/**
		 * \var key_
		 * \brief an array of booleans to track if the key is currently up or down
		 */
		bool key_[KEY::Key_Max];
		
		/**
		 * \var keys_
		 * \brief an array of booleans to track if a key was pressed (used in non-repeating key handling)
		 */
		bool keys_[KEY::Key_Max];
		
		/**
		 * \var joystickAvailable_
		 * \brief this variable is true when we successfully load the joystick calibration data file
		 */
		bool joystickAvailable_;
		
	}; // end class

/**
 * \def InputDevice
 * \brief an alias to the InputDeviceSingleton::GetInstance() function
 */
#define InputDevice InputDeviceSingleton::GetInstance()
} // end namespace
#endif


