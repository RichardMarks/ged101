
// CODESTYLE: v2.0

// GameTimer.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A cross-platform compatible class for handling proper game timing

/**
 * \file GameTimer.h
 * \brief Cross-platform high-resolution timer class - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */
 
#ifndef __GAMETIMER_H__
#define __GAMETIMER_H__

/**
 * \def GameTimerMethodReturnType
 * \brief depending on the OS that the code is being compiled for, this will be either a linux data structure or a simple integer
 */
// only non-windows platforms use this
#if !defined(WIN32)
#define GameTimerMethodReturnType time_t

//! we define the __time_t data type so we don't need to include the linux time headers in our header
typedef long int __time_t;
//! we define the time_t data type so we don't need to include the linux time headers in our header
typedef __time_t time_t;
//! we declare the timeval data type as a struct so we don't need to include the linux time headers in our header
struct timeval;
#else
// this is for the windows platform
#define GameTimerMethodReturnType DWORD
#endif

namespace ENGINE
{
	/**
	 * \class GameTimerSingleton
	 * \brief A cross-platform compatible class for handling proper game timing
	 * \ingroup SystemGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 *
	 * This is a high-resolution timer that wraps up the tricky code needed to
	 * implement proper timing in your games. And it is cross-platform as well!
	 *
	 * The GameTimerSingleton is clearly implemented as a singleton class.
	 * Which means that there is only ever a single instance of the class at all times.
	 * You access the methods by using the macro "GameTimer" and a pointer.
	 *
	 * such as: time_t ms = GameTimer->GetMilliseconds();
	 */
	class GameTimerSingleton
	{
	public:
		// public members should be declared here
		
		/**
		 * \return a pointer to the singleton class
		 */
		static GameTimerSingleton* GetInstance();
		
		/**
		 * destructor De-allocates any allocated memory
		 */
		~GameTimerSingleton();
		
		/**
		 * Get the number of microseconds passed since the last call.\n
		 * There are approximately 1000 microseconds in 1 millisecond.
		 * \return the number of microseconds passed since the last call.
		 */
		GameTimerMethodReturnType GetMicroseconds();
		
		/**
		 * Get the number of milliseconds passed since the last call.\n
		 * There are approximately 1000 milliseconds in 1 second.
		 * \return the number of milliseconds passed since the last call.
		 */
		GameTimerMethodReturnType GetMilliseconds();
		
		/**
		 * \return the number of seconds passed since the last call.
		 */
		GameTimerMethodReturnType GetSeconds();
		
	private:
		// private members should be declared here
		/**
		 * default constructor is hidden
		 */
		GameTimerSingleton();
		
		/**
		 * The copy constructor is hidden
		 */
		GameTimerSingleton(const GameTimerSingleton& rhs);
		
		/**
		 * The assignment operator is hidden
		 */
		GameTimerSingleton& operator=(const GameTimerSingleton& rhs);
		
		/**
		 * \var startTime_ 
		 * \brief the time when the timer was created.
		 */
		 
		/**
		 * \var currentTime_ 
		 * \brief the current time of the timer.
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
 * \def GameTimer
 * \brief an alias for GameTimerSingleton::GetInstance()
 */
#define GameTimer GameTimerSingleton::GetInstance()
} // end namespace
#endif


