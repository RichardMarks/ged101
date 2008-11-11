
// CODESTYLE: v2.0

// Audio.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: This class wraps audio resource loading, playback, destruction functionality.

#ifndef __AUDIO_H__
#define __AUDIO_H__

struct SAMPLE;

namespace ENGINE
{
	class AudioStreamResource_OGG;
	class AudioSampleResource_OGG;
	class Audio
	{
	public:
		/**
		* OGG/Vorbis Streaming Audio (music)
		*/
		static int OpenStream_OGG(AudioStreamResource_OGG* resource);
		static void DestroyStream_OGG(AudioStreamResource_OGG* resource);
		static int PlayStream_OGG(AudioStreamResource_OGG* resource);
		static int ReadData_OGG(AudioStreamResource_OGG* resource);
		static AudioStreamResource_OGG* GetStream_OGG(const char* fileName, int volume, int pan, int loop);
		static int UpdateStream_OGG(AudioStreamResource_OGG* resource);
		static void StopStream_OGG(AudioStreamResource_OGG* resource);
		static int RestartStream_OGG(AudioStreamResource_OGG* resource);
		
		/**
		* OGG/Vorbis Sample Audio (sound effects)
		*/
		static SAMPLE* CreateSample_OGG(const char* fileName);
		static AudioSampleResource_OGG* OpenSample_OGG(const char* fileName);
		static void DestroySample_OGG(const AudioSampleResource_OGG* resource);
		static int PlaySample_OGG(const AudioSampleResource_OGG* resource, int volume = 128, int pan = 128, int frequency = 1000, int loop = 0);
		static void StopSample_OGG(const AudioSampleResource_OGG* resource);
		static void ModifySample_OGG(const AudioSampleResource_OGG* resource, int volume = 128, int pan = 128, int frequency = 1000, int loop = 0);
		
	private:
		/**
		* The class constructor is private because this is just an interface class.
		*/
		Audio(){};
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		Audio(const Audio& rhs);
		Audio& operator=(const Audio& rhs);
	}; // end class

} // end namespace
#endif


