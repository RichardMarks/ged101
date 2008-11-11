
// CODESTYLE: v2.0

// GameTimer.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A cross-platform compatible class for handling proper game timing

#ifndef __GAMETIMER_H__
#define __GAMETIMER_H__

// only non-windows platforms use this
#if !defined(WIN32)
#define GameTimerMethodReturnType time_t
typedef long int __time_t;
typedef __time_t time_t;
struct timeval;
#else
// this is for the windows platform
#define GameTimerMethodReturnType DWORD
#endif

namespace ENGINE
{
	/**
	* This is a high-resolution timer that wraps up the tricky code needed to
	* implement proper timing in your games. And it is cross-platform as well!
	*
	* The GameTimerSingleton is clearly implemented as a singleton class.
	* Which means that there is only ever a single instance of the class at all times.
	* You access the methods by using the macro "GameTimer" and a pointer.
	*
	* such as: time_t ms = GameTimer->GetMilliseconds();
	*
	*/
	class GameTimerSingleton
	{
	public:
		// public members should be declared here
		
		/**
		* As was stated before, this class is a singleton, and this is the static method
		* that returns the pointer to the singleton instance of the class.
		*/
		static GameTimerSingleton* GetInstance();
		
		/**
		* The class destructor handle releasing allocated resources
		*/
		~GameTimerSingleton();
		
		/**
		* Returns the number of microseconds passed since the last call.
		*
		* There are approximately 1000 microseconds in 1 millisecond.
		*/
		GameTimerMethodReturnType GetMicroseconds();
		
		/**
		* Returns the number of milliseconds passed since the last call.
		*
		* There are approximately 1000 milliseconds in 1 second.
		*/
		GameTimerMethodReturnType GetMilliseconds();
		
		/**
		* Returns the number of seconds passed since the last call.
		*/
		GameTimerMethodReturnType GetSeconds();
		
	private:
		// private members should be declared here
		/**
		* The class constructor is private because this is a singleton.
		*/
		GameTimerSingleton();
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		GameTimerSingleton(const GameTimerSingleton& rhs);
		GameTimerSingleton& operator=(const GameTimerSingleton& rhs);
		
		/**
		* startTime_ is the time when the timer was created.
		* currentTime_ is the current time of the timer.
		*/
// only non-windows platforms use this
#if !defined(WIN32)
		timeval* startTime_;
		timeval* currentTime_;
#else
// this is for the windows platform
		unsigned long long startTime_;
		unsigned long long currentTime_;
#endif
	}; // end class

/**
* The GameTimer MACRO is the preferred way to use the timer class singleton pointer.
*/
#define GameTimer GameTimerSingleton::GetInstance()
} // end namespace
#endif


