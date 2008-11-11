
// CODESTYLE: v2.0

// AudioFormats.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks

#ifndef __AUDIOFORMATS_H__
#define __AUDIOFORMATS_H__

// Add your prototypes, includes, constants, etc here

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

// forward declare the Allegro data structures we need
struct AUDIOSTREAM;
struct SAMPLE;

namespace ENGINE
{
	const unsigned int AUDIORESOURCE_OGG_BUFFER_PAGES 	= 0x2;
	const unsigned int AUDIORESOURCE_OGG_BUFFER_SIZE 	= 1024 * 64;
	
	class AudioStreamResource_OGG
	{
	public:
		/**
		* The name of the file that is to be streamed.
		*/
		char* fileName_;
		
		/**
		* The audio buffer used in decoding the stream.
		*/
		char* buffer_[AUDIORESOURCE_OGG_BUFFER_PAGES];
		
		/**
		* The Allegro audio stream structure.
		*/
		AUDIOSTREAM* allegroAudioStream_;
		
		/**
		* The OGG/Vorbis data structure
		*/
		OggVorbis_File vorbisFile_;	
		
		/**
		*
		*/
		int currentBufferPage_;
		int playingBufferPage_;
		int stereo_;
		int frequency_;
		int bits_;
		int length_;
		int loop_;
		int volume_;
		int pan_;
		bool stopped_;
	};

	class AudioSampleResource_OGG
	{
	public:
		SAMPLE* allegroSample_;
	};

} // end namespace

#endif

