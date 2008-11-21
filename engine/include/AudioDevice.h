
// CODESTYLE: v2.0

// AudioDevice.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Interface to the audio hardware device

/**
 * \file AudioDevice.h
 * \brief Input Device Interface Module - Header 
 */

#ifndef __AUDIODEVICE_H__
#define __AUDIODEVICE_H__

namespace ENGINE
{
	/**
	 * \class AudioDeviceSingleton
	 * \brief Interface to the audio hardware 
	 *
	 * Support for getting and setting the volume of audio playback
	 */
	class AudioDeviceSingleton
	{
	public:
		// public members should be declared here

		/**
		 * \return a pointer to the class singleton
		 */
		static AudioDeviceSingleton* GetInstance();

		/**
		 * Installs the audio driver the first time the function is called.
		 * You need to call this function at least once before you try to load or playback any audio files!
		 */
		void Initialize();

		/**
		 * Sets the local volume for just your program.
		 * @param volume is an integer that should be set from 0 (off) to 255 (full blast)
		 */
		void SetLocalVolume(int volume);
		
		/**
		 * Sets the local volume for your whole computer.
		 * @param volume is an integer that should be set from 0 (off) to 255 (full blast)
		 */
		void SetGlobalVolume(int volume);
		
		/**
		 * \return the volume for just your program. This will be an integer from 0 (off) to 255 (full blast)
		 */
		int GetLocalVolume();
		
		/**
		 * \return the volume for your whole computer. This will be an integer from 0 (off) to 255 (full blast)
		 */
		int GetGlobalVolume();

		/**
		 * De-allocates any allocated memory by calling AudioDeviceSingleton::Destroy()
		 */
		~AudioDeviceSingleton();
		
	private:
	
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * default constructor is hidden
		 */
		AudioDeviceSingleton();
		
		/**
		 * copy constructor is hidden
		 */
		AudioDeviceSingleton(const AudioDeviceSingleton& rhs);
		
		/**
		 * assignment operator is hidden
		 */
		const AudioDeviceSingleton& operator=(const AudioDeviceSingleton& rhs);
		
		/**
		 * \var localVolume_
		 * \brief the volume of just the running program
		 */
		int localVolume_;
		
		/**
		 * \var localVolume_
		 * \brief the volume of the entire computer
		 */
		int globalVolume_;
	}; // end class

/**
 * \def AudioDevice
 * \brief an alias to AudioDeviceSingleton::GetInstance()
 */
#define AudioDevice AudioDeviceSingleton::GetInstance()
} // end namespace
#endif


