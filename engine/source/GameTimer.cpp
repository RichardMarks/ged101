
// CODESTYLE: v2.0

// GameTimer.cpp
// Project: GameTimer Project (ENGINE)
// Author: Richard Marks
// Purpose: A cross-platform compatible class for handling proper game timing

// only non-windows platforms use this
#if !defined(WIN32)
#include <ctime>
#include <sys/time.h>
#else
// this is for the windows platform
#include <windows.h>
#endif

// include the complementing header
#include "GameTimer.h"

namespace ENGINE
{
	GameTimerSingleton* GameTimerSingleton::GetInstance()
	{
		// return the singleton instance
		static GameTimerSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	GameTimerSingleton::GameTimerSingleton() :
		startTime_(0),
		currentTime_(0)
	{
		// implement class constructor here
// only non-windows platforms use this
#if !defined(WIN32)
		startTime_ = new timeval;
		currentTime_ = new timeval;
		gettimeofday(startTime_, 0);
#else
// this is for the windows platform
		startTime_ = GetTickCount();
		currentTime_ = startTime_;
#endif
	} // end constructor
	
	/**************************************************************************/
	
	GameTimerSingleton::~GameTimerSingleton()
	{
		// implement class destructor here
// only non-windows platforms use this
#if !defined(WIN32)
		if (0 != startTime_) { delete startTime_; startTime_ = 0; }
		if (0 != currentTime_) { delete currentTime_; currentTime_ = 0; }
#else
// this is for the windows platform
	startTime_ = 0;
	currentTime_ = 0;
#endif
	} // end destructor
	
	/**************************************************************************/
	
	GameTimerMethodReturnType GameTimerSingleton::GetMicroseconds()
	{
// only non-windows platforms use this
#if !defined(WIN32)
		gettimeofday(currentTime_, 0);
		return static_cast<GameTimerMethodReturnType>(
			((currentTime_->tv_sec - startTime_->tv_sec) / 1000) +
			((currentTime_->tv_usec - startTime_->tv_usec)));
#else
// this is for the windows platform
		static bool firstCall = true;
		static unsigned long long frequency = 0;
		if (firstCall)
		{
			QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
			firstCall = false; 
		}
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime_);
		currentTime_ *= 1000000;
		currentTime_ /= frequency;
		return static_cast<GameTimerMethodReturnType>(currentTime_ - (startTime_ * 1000));
#endif
	}
	
	/**************************************************************************/
	
	GameTimerMethodReturnType GameTimerSingleton::GetMilliseconds()
	{
// only non-windows platforms use this
#if !defined(WIN32)
		gettimeofday(currentTime_, 0);
		return static_cast<GameTimerMethodReturnType>(
			((currentTime_->tv_sec - startTime_->tv_sec) * 1000) +
			((currentTime_->tv_usec - startTime_->tv_usec) / 1000));
#else
// this is for the windows platform
		currentTime_ = GetTickCount();
		return static_cast<GameTimerMethodReturnType>(currentTime_ - startTime_);
#endif
	}
	
	/**************************************************************************/
	
	GameTimerMethodReturnType GameTimerSingleton::GetSeconds()
	{
// only non-windows platforms use this
#if !defined(WIN32)
		gettimeofday(currentTime_, 0);
		return static_cast<GameTimerMethodReturnType>(
			(currentTime_->tv_sec - startTime_->tv_sec));
#else
// this is for the windows platform
		currentTime = GetTickCount();
		return static_cast<GameTimerMethodReturnType>((currentTime_ - startTime_) / 1000);
#endif
	}

} // end namespace


