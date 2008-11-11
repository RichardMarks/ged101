
// CODESTYLE: v2.0

// InputManager.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: This class wraps keyboard, mouse, and joystick functionality.

#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

namespace ENGINE
{
	/**
	* This class wraps keyboard, mouse, and joystick functionality.
	*
	* The InputManagerSingleton is clearly implemented as a singleton class.
	* Which means that there is only ever a single instance of the class at all times.
	* You access the methods by using the macro "InputManager" and a pointer.
	*
	* such as: ENGINE::InputManager->KeyPressed();
	*
	*/
	class ImageResource;
	class InputManagerSingleton
	{
	public:
		// public members should be declared here
		/**
		* As was stated before, this class is a singleton, and this is the static method
		* that returns the pointer to the singleton instance of the class.
		*/
		static InputManagerSingleton* GetInstance();
		
		/**
		* The class destructor handle releasing allocated resources
		*/
		~InputManagerSingleton();
		
		/**
		* You need to call this before you can use the other methods.
		*/
		void Initialize();
		
		// keyboard functionality
		bool KeyPressed(int keyCode);
		bool KeyDown(int keyCode);
		bool KeyUp(int keyCode);
		bool KeyPressed(int modifier, int keyCode);
		bool KeyDown(int modifier, int keyCode);
		bool KeyUp(int modifier, int keyCode);
		
		
		// mouse functionality
		bool MouseButtonDown(int button);
		bool MouseButtonUp(int button);
		int MouseX();
		int MouseY();
		int MouseZ();
		int MouseMoveRelative(int axis);
		void MouseSetPosition(int x, int y, int z = 0);
		void MouseSetRegion(int left, int top, int right, int bottom);
		void MouseSetSpeed(int speedX, int speedY);
		void MouseSetCursorImage(ImageResource* image = 0, int hotSpotX = 0, int hotSpotY = 0);
		
		// joystick functionality
		void BeginJoystickCalibration();
		static bool JoyExists(int joystick);
		static bool JoyButtonExists(int joystick, int button);
		static bool JoyStickExists(int joystick, int stick);
		// digital joystick input
		bool JoyButtonDown(int button, int joystick = 0);
		bool JoyButtonUp(int button, int joystick = 0);
		bool JoyUp(int joystick = 0, int stick = 0);
		bool JoyDown(int joystick = 0, int stick = 0);
		bool JoyLeft(int joystick = 0, int stick = 0);
		bool JoyRight(int joystick = 0, int stick = 0);
		
		// analogue joystick input
		int Joy(int axis, int stick = 0, int joystick = 0);
		
		void Update();
		
	private:
		// private members should be declared here
		/**
		* The class constructor is private because this is a singleton.
		*/
		InputManagerSingleton();
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		InputManagerSingleton(const InputManagerSingleton& rhs);
		InputManagerSingleton& operator=(const InputManagerSingleton& rhs);
		
		bool key_[255]; // used in key down or up
		bool keys_[255]; // used in key pressed
		
		bool joystickAvailable_; // will be true only when we successfully loaded the joystick calibration
		
	}; // end class

/**
* The InputManager MACRO is the preferred way to use the input manager class singleton pointer.
*/
#define InputManager InputManagerSingleton::GetInstance()
} // end namespace
#endif


