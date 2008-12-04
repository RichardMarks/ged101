
// CODESTYLE: v2.0

// AudioDevice.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Interface to the audio hardware device

/**
 * \file AudioDevice.h
 * \brief Audio Device Interface Module - Header 
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __AUDIODEVICE_H__
#define __AUDIODEVICE_H__

namespace ENGINE
{
	/**
	 * \class AudioDeviceSingleton
	 * \brief Interface to the audio hardware 
	 * \ingroup AudioGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 *
	 * The AudioDeviceSingleton class gives you the ability to manipulate the volume of audio playback.
	 * You can get and set the volume for both your game, and the whole computer.
	 */
	class AudioDeviceSingleton
	{
	public:
		// public members should be declared here

		/**
		 * Gets the device interface
		 * \return a pointer to the class singleton
		 *
		 * Because this class is a singleton, it cannot be instantiated, 
		 * and you must use this function to be able to access the member functions.
		 * \code
// get a pointer to the audio device interface class singleton
ENGINE::AudioDeviceSingleton::GetInstance()
		 * \endcode
		 */
		static AudioDeviceSingleton* GetInstance();

		/**
		 * Installs the audio driver the first time the function is called.
		 * You need to call this function at least once before you try to load or playback any audio files!
		 * 
		 * You can initialize the audio device interface with the full name of the class
		 * \code
// initialize the audio device interface
ENGINE::AudioDeviceSingleton::GetInstance()->Initialize();
		 * \endcode
		 * or using the \a #define alias
		 * \code
// initialize the audio device interface
ENGINE::AudioDevice->Initialize();
		 * \endcode
		 */
		void Initialize();

		/**
		 * Sets the local volume for just your program.
		 * @param volume is an integer that should be set from 0 (off) to 255 (full blast)
		 * \code
// turn the volume off for your program
ENGINE::AudioDeviceSingleton::GetInstance()->SetLocalVolume(0);

// turn the volume up to maximum for your program
ENGINE::AudioDeviceSingleton::GetInstance()->SetLocalVolume(255);
		 * \endcode
		 */
		void SetLocalVolume(int volume);
		
		/**
		 * Sets the local volume for your whole computer.
		 * @param volume is an integer that should be set from 0 (off) to 255 (full blast)
		 * \code
// turn the volume off for your computer
ENGINE::AudioDeviceSingleton::GetInstance()->SetGlobalVolume(0);

// turn the volume up to maximum for your computer
ENGINE::AudioDeviceSingleton::GetInstance()->SetGlobalVolume(255);
		 * \endcode
		 */
		void SetGlobalVolume(int volume);
		
		/**
		 * Gets your program's volume
		 * \return the volume for just your program. This will be an integer from 0 (off) to 255 (full blast)
		 * \code
// get the volume level for your program
int currentVolume = ENGINE::AudioDeviceSingleton::GetInstance()->GetLocalVolume();
		 * \endcode
		 */
		int GetLocalVolume();
		
		/**
		 * Gets the computer's volume
		 * \return the volume for your whole computer. This will be an integer from 0 (off) to 255 (full blast)
		 * \code
// get the volume level for your computer
int currentVolume = ENGINE::AudioDeviceSingleton::GetInstance()->GetGlobalVolume();
		 * \endcode
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


