
// CODESTYLE: v2.0

// AudioDevice.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Implementation for the interface to the audio hardware device

/**
 * \file AudioDevice.cpp
 * \brief Audio Device Interface Module - Implementation 
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "AudioDevice.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	AudioDeviceSingleton* AudioDeviceSingleton::GetInstance()
	{
		static AudioDeviceSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	void AudioDeviceSingleton::Initialize()
	{
		static bool firstCall = true;
		
		if (firstCall)
		{
			if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) < 0)
			{
				LogFatal("Could not install the Allegro audio driver! Try using the --quiet command line flag.");
			}
		}
		
		int garbage;
		
		get_volume(&localVolume_, &garbage);
		get_hardware_volume(&globalVolume_, &garbage);
	}
	
	/**************************************************************************/
	
	void AudioDeviceSingleton::SetLocalVolume(int volume)
	{
		localVolume_ = volume;
	}
	
	/**************************************************************************/
	
	void AudioDeviceSingleton::SetGlobalVolume(int volume)
	{
		globalVolume_ = volume;
	}
	
	/**************************************************************************/
	
	int AudioDeviceSingleton::GetLocalVolume()
	{
		int garbage;
		get_volume(&localVolume_, &garbage);
		return localVolume_;
	}
	
	/**************************************************************************/
	
	int AudioDeviceSingleton::GetGlobalVolume()
	{
		int garbage;
		get_hardware_volume(&globalVolume_, &garbage);
		return globalVolume_;
	}
	
	/**************************************************************************/
	
	void AudioDeviceSingleton::Destroy()
	{
		// nothing to de-allocate
	}
	
	/**************************************************************************/
	
	AudioDeviceSingleton::AudioDeviceSingleton() :
		localVolume_(128),
		globalVolume_(128)
	{
	} // end constructor

	/**************************************************************************/
	
	AudioDeviceSingleton::~AudioDeviceSingleton()
	{
		// implement class destructor here
		Destroy();
	} // end destructor

} // end namespace


