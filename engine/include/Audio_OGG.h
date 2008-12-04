
// CODESTYLE: v2.0

// Audio_OGG.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks - created with help from many source references found on the web and from friends.
// Purpose: These classes wrap the OGG/Vorbis audio resource loading, playback, destruction functionality.

/**
 * \file Audio_OGG.h
 * \brief OGG/Vorbis Audio Resource - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __AUDIO_OGG_H__
#define __AUDIO_OGG_H__

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

// forward declare the Allegro data structures we need
struct AUDIOSTREAM;
struct SAMPLE;

namespace ENGINE
{
	//! number of pages of audio data to buffer
	const unsigned int AUDIORESOURCE_OGG_BUFFER_PAGES 	= 0x2;
	
	//! size of the audio data buffer
	const unsigned int AUDIORESOURCE_OGG_BUFFER_SIZE 	= 1024 * 64;
	
	/**
	 * \class AudioSampleResource_OGG
	 * \brief A class for using short audio samples in the OGG format
	 * \ingroup AudioGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class AudioSampleResource_OGG
	{
	public:
		AudioSampleResource_OGG();
		~AudioSampleResource_OGG();

		/**
		 * Loads an audio sample from a file.
		 * @param fileName is the name of the file that holds the audio sample data to load.
		 * \return true if the audio sample was loaded, and false otherwise.
		 */
		bool Load(const char* fileName);
		
		/**
		 * Starts playing an audio sample at the specified frequency, volume, and pan settings.
		 * @param volume ranges from 0 (minimum volume) to 255 (maximum volume)
		 * @param pan ranges from 0 (left) to 255 (right)
		 * @param frequency is a relative value. 1000 is the frequency the sample was recorded at, 2000 is twice the frequency.
		 * @param loop can be set to 1 or 0. If it is set to 1, then the sample will loop until AudioSampleResource_OGG::Stop() is called.
		 * \return the voice number that was allocated for the sample or negative if no voices were available.
		 */
		int Play(int volume = 128, int pan = 128, int frequency = 1000, int loop = 0);
		
		/**
		 * Modifies the parameters of an audio sample while it is playing (useful for manipulating looped sounds). 
		 * You can modify the volume, pan, and frequency, and can also clear the loop flag, 
		 * which will stop the sample when it next reaches the end of its loop. 
		 * The values of the parameters are just like those of AudioSampleResource_OGG::Play(). 
		 * If the audio sample is not playing, this function has no effect. 
		 * @param volume ranges from 0 (minimum volume) to 255 (maximum volume)
		 * @param pan ranges from 0 (left) to 255 (right)
		 * @param frequency is a relative value. 1000 is the frequency the sample was recorded at, 2000 is twice the frequency.
		 * @param loop can be set to 1 or 0. If it is set to 1, then the sample will loop until AudioSampleResource_OGG::Stop() is called.
		 */
		void Modify(int volume = 128, int pan = 128, int frequency = 1000, int loop = 0);
		
		/**
		 * Stops the audio sample if it is playing.
		 */
		void Stop();
		
		/**
		 * De-allocates any allocated memory for the audio sample.
		 */
		void Destroy();
		
		/**
		 * \return AudioSampleResource_OGG::allegroSample_ or 0 if the audio sample is invalid.
		 */
		SAMPLE* GetAllegroSample();
		
	private:
		/**
		 * \var allegroSample_
		 * \brief An allegro SAMPLE structure
		 *
		 * Below is the SAMPLE structure straight from the Allegro documentation
		 * \code
typedef struct SAMPLEtag
{
	int bits;                   - 8 or 16
	int stereo;                 - sample type flag
	int freq;                   - sample frequency
	int priority;               - 0-255
	unsigned long len;          - length (in samples)
	unsigned long loop_start;   - loop start position
	unsigned long loop_end;     - loop finish position
	void *data;                 - raw sample data
} SAMPLE;
		 * \endcode
		 * A sample structure, which holds sound data, used by the digital sample routines. 
		 * You can consider all of these fields as read only except priority, loop_start and loop_end, 
		 * which you can change them for example after loading a sample from disk.
		 * \n
		 * The priority is a value from 0 to 255 (by default set to 128) and controls how hardware voices on 
		 * the sound card are allocated if you attempt to play more than the driver can handle. This may be used 
		 * to ensure that the less important sounds are cut off while the important ones are preserved.

		 * The variables loop_start and loop_end specify the loop position in sample units, and are set by default 
		 * to the start and end of the sample.

		 * If you are creating your own samples on the fly, you might also want to modify the raw data of 
		 * the sample pointed by the data field. The sample data are always in unsigned format. 
		 * This means that if you are loading a PCM encoded sound file with signed 16-bit samples, 
		 * you would have to XOR every two bytes (i.e. every sample value) with 0x8000 to change the signedness. 
		 */
		SAMPLE* allegroSample_;
	}; // end class

	/**
	 * \class AudioStreamResource_OGG
	 * \brief A class for using long audio data streams (background music) in the OGG format
	 * \ingroup AudioGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class AudioStreamResource_OGG
	{
	public:
		AudioStreamResource_OGG();
		~AudioStreamResource_OGG();
		
		/**
		 * Loads an audio stream from a file.
		 * @param fileName is the name of the file that holds the audio stream data to load.
		 * @param volume ranges from 0 (minimum volume) to 255 (maximum volume)
		 * @param pan ranges from 0 (left) to 255 (right)
		 * @param loop can be set to 1 or 0. If it is set to 1, then the stream will loop until AudioStreamResource_OGG::Stop() is called.
		 * \return true if the audio stream was loaded, and false otherwise.
		 */
		bool Load(const char* fileName, int volume = 128, int pan = 128, int loop = 1);
		
		/**
		 * plays the audio stream. call this once per frame to keep the audio playing
		 */
		int Update();
		
		/**
		 * Stops an audio stream from playing
		 */
		void Stop();
		
		/**
		 * Restarts a stopped audio stream
		 */
		int Restart();
		
		/**
		 * De-allocates memory allocated for the audio stream
		 */
		void Destroy();
		
	private:
		/**
		 * streaming support function
		 */
		int OpenStream();
		
		/**
		 * streaming support function
		 */
		int ReadStreamData();
		
		/**
		 * streaming support function
		 */
		int PlayStream();
		
	private:
		//! The name of the file that contains the audio data to be streamed
		char* fileName_;
		
		//! The audio buffer used in decoding the stream.
		char* buffer_[AUDIORESOURCE_OGG_BUFFER_PAGES];
		
		//! The Allegro audio stream structure.
		AUDIOSTREAM* allegroAudioStream_;
		
		//! The OGG/Vorbis data structure
		OggVorbis_File vorbisFile_;	
		
		//! the index of the current buffer page
		int currentBufferPage_;
		
		//! the index of the buffer page that is playing
		int playingBufferPage_;
		
		//! undocumented variable
		int stereo_;
		
		//! undocumented variable
		int frequency_;
		
		//! undocumented variable
		int bits_;
		
		//! undocumented variable
		int length_;
		
		//! undocumented variable
		int loop_;
		
		//! undocumented variable
		int volume_;
		
		//! undocumented variable
		int pan_;
		
		//! undocumented variable
		bool stopped_;
	}; // end class

} // end namespace
#endif


