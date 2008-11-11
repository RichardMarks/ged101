
// CODESTYLE: v2.0

// Audio_OGG.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks - created with help from many source references found on the web and from friends.
// Purpose: This class wraps the OGG/Vorbis audio resource loading, playback, destruction functionality.

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "Audio.h"

// include the audio formats header
#include "AudioFormats.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	/**
	* Opens an OGG/Vorbis file for streaming.
	* Returns zero on success, and one on failure.
	*/
	int Audio::OpenStream_OGG(AudioStreamResource_OGG* resource)
	{
		FILE* fp;
		vorbis_info* vorbisInfo;
		fp = fopen(resource->fileName_, "rb");
		if (!fp)
		{
			char e[256]; sprintf(e, "Could not load the file %s", resource->fileName_); LogFatal(e);
		}
	
		int ovResult = ov_open_callbacks(fp, &resource->vorbisFile_, 0, 0, OV_CALLBACKS_DEFAULT);
		if (0 != ovResult)
		{
			switch(ovResult)
			{
				case OV_EREAD:
				{
					LogFatal("ov_open_callbacks Error - A read from media returned an error.");
				} break;
		
				case OV_ENOTVORBIS:
				{
					LogFatal("ov_open_callbacks Error - Bitstream does not contain any Vorbis data.");
				} break;
		
				case OV_EVERSION:
				{
					LogFatal("ov_open_callbacks Error - Vorbis version mismatch.");
				} break;
		
				case OV_EBADHEADER:
				{
					LogFatal("ov_open_callbacks Error - Invalid Vorbis bitstream header.");
				} break;
		
				case OV_EFAULT:
				{
					LogFatal("ov_open_callbacks Error - Internal logic fault; indicates a bug or heap/stack corruption.");
				} break;
			}
			return 1;
		}
	
		vorbisInfo = ov_info(&resource->vorbisFile_, -1);
	
		char infoMsg[512];
		sprintf(infoMsg, 
			"\nVorbis Encoder Version: %d\n"
			"Channels: %d\n"
			"Sampling Rate: %d\n"
			"Bitstream Upper Limit: %d\n"
			"Bitstream Lower Limit: %d\n"
			"Bitstream Average Bitrate: %d\n",
			vorbisInfo->version,
			vorbisInfo->channels,
			vorbisInfo->rate,
			vorbisInfo->bitrate_upper,
			vorbisInfo->bitrate_lower,
			vorbisInfo->bitrate_nominal
			);
		LogMessage(infoMsg);
	
		resource->bits_ 				= 16;
		resource->stereo_ 				= (vorbisInfo->channels > 1) ? 1 : 0;
		resource->frequency_ 			= vorbisInfo->rate;
		resource->length_ 				= ov_pcm_total(&resource->vorbisFile_, -1);
		
		return 0;
	}
	
	/**************************************************************************/
	
	/**
	* Releases memory allocated for the stream.
	*/
	void Audio::DestroyStream_OGG(AudioStreamResource_OGG* resource)
	{
		if (!resource->stopped_)
		{
			Audio::StopStream_OGG(resource);
		}
		
		ov_clear(&resource->vorbisFile_);
		free(resource->fileName_);
		free(resource);
	}
	
	/**************************************************************************/
	
	/**
	* Streams the audio data
	* Returns zero on success, and one on failure.
	*/
	int Audio::PlayStream_OGG(AudioStreamResource_OGG* resource)
	{
		resource->currentBufferPage_ 	= 0;
		resource->playingBufferPage_ 	= -1;

		int bitsDiv = static_cast<int>((resource->bits_ / (sizeof(char) * 8)));
		
		int bufferDiv = static_cast<int>(AUDIORESOURCE_OGG_BUFFER_SIZE / (resource->stereo_ ? 2 : 1));
		
		bitsDiv = (bitsDiv <= 0) ? 1 : bitsDiv;
		
		resource->allegroAudioStream_ 	= play_audio_stream(
			static_cast<int>(bufferDiv / bitsDiv), 
			resource->bits_, 
			resource->stereo_, 
			resource->frequency_, 
			resource->volume_, 
			resource->pan_);

		if (!resource->allegroAudioStream_)
		{
			LogFatal("Failed to create Allegro Audio Stream!");
		}
		
		for (int index = 0; index < AUDIORESOURCE_OGG_BUFFER_PAGES; index++)
		{
			resource->buffer_[index] = static_cast<char*>(malloc(AUDIORESOURCE_OGG_BUFFER_SIZE));
			
			if (!resource->buffer_[index])
			{
				LogError("Could not allocate audio buffer!");
				Audio::DestroyStream_OGG(resource);
				return 1;
			}
			
			if (Audio::ReadData_OGG(resource) < 0) 
			{
				return 1;
			}
		}
		
		resource->stopped_ = false;
		return 0;
	}
	
	/**************************************************************************/
	
	/**
	* Reads the audio data
	* Returns the number of bytes of audio data read.
	*/
	int Audio::ReadData_OGG(AudioStreamResource_OGG* resource)
	{
		int bytesOfDataRead = 0;
		int bitstream = 0;
		int page = resource->currentBufferPage_;
		
		resource->currentBufferPage_++;
		resource->currentBufferPage_ %= AUDIORESOURCE_OGG_BUFFER_PAGES;
		memset(resource->buffer_[page], 0, AUDIORESOURCE_OGG_BUFFER_SIZE);

		while (bytesOfDataRead < AUDIORESOURCE_OGG_BUFFER_SIZE) 
		{
			int thisRead = ov_read(&resource->vorbisFile_, 
				resource->buffer_[page] + bytesOfDataRead,
				AUDIORESOURCE_OGG_BUFFER_SIZE - bytesOfDataRead,
				0, 
				2, 
				0, 
				&bitstream);
				
			if (0 == thisRead) 
			{
				if (resource->loop_) 
				{
					ov_clear(&resource->vorbisFile_);
					if (Audio::OpenStream_OGG(resource))
					{
						return -1;
					}
				}
				else 
				{
					return bytesOfDataRead;
				}
			}
			bytesOfDataRead += thisRead;
		}
		return bytesOfDataRead;
	}
	
	/**************************************************************************/
	
	/**
	* Loads an OGG/Vorbis file to be streamed.
	* Returns a pointer to an OGG/Vorbis Audio Stream Resource
	*/
	AudioStreamResource_OGG* Audio::GetStream_OGG(const char* fileName, int volume, int pan, int loop)
	{
		AudioStreamResource_OGG* resource = static_cast<AudioStreamResource_OGG*>(calloc(1, sizeof(AudioStreamResource_OGG)));
		
		if (!resource)
		{
			LogError("Could not allocate resource!");
			return 0;
		}

		resource->fileName_ = strdup(fileName);

		if (!resource->fileName_)
		{
			free(resource);
			return 0;
		}
		
		if (Audio::OpenStream_OGG(resource))
		{
			Audio::DestroyStream_OGG(resource);
			return 0;
		}
		
		resource->volume_ 				= volume;
		resource->pan_ 					= pan;
		resource->loop_ 				= loop;
		
		if (Audio::PlayStream_OGG(resource))
		{
			Audio::DestroyStream_OGG(resource);
			return 0;
		}
		return resource;
	}
	
	/**************************************************************************/
	
	/**
	* Refills the audio stream buffer with data.
	*/
	int Audio::UpdateStream_OGG(AudioStreamResource_OGG* resource)
	{
		if (resource->stopped_)
		{
			Audio::RestartStream_OGG(resource);
		}
		unsigned char* data = static_cast<unsigned char*>(get_audio_stream_buffer(resource->allegroAudioStream_));
		if (!data) 
		{
			if (resource->currentBufferPage_ != resource->playingBufferPage_) 
			{
				int read = Audio::ReadData_OGG(resource);
				if (read < AUDIORESOURCE_OGG_BUFFER_SIZE)
				{
					return 0;
				}
				else 
				{
					return 1;
				}
			}
			else 
			{
				return 1;
			}
		}
		resource->playingBufferPage_++;
		resource->playingBufferPage_ %= AUDIORESOURCE_OGG_BUFFER_PAGES;
		memcpy(data, resource->buffer_[resource->playingBufferPage_], AUDIORESOURCE_OGG_BUFFER_SIZE);
		free_audio_stream_buffer(resource->allegroAudioStream_);
		return 1;
	}
	
	/**************************************************************************/
	
	/**
	* Halts the playing audio stream
	*/
	void Audio::StopStream_OGG(AudioStreamResource_OGG* resource)
	{
		stop_audio_stream(resource->allegroAudioStream_);
		for (int index = 0; index < AUDIORESOURCE_OGG_BUFFER_PAGES; index++) 
		{
			free(resource->buffer_[index]);
			resource->buffer_[index] = 0;
		}
		resource->stopped_ = true;
	}
	
	/**************************************************************************/
	
	/**
	* Restarts the audio stream
	*/
	int Audio::RestartStream_OGG(AudioStreamResource_OGG* resource)
	{
		resource->stopped_ = false;
		return Audio::PlayStream_OGG(resource);
	}
	
	/**************************************************************************/
	
	/**
	* Loads an OGG/Vorbis file into an Allegro SAMPLE structure.
	* Returns a pointer to an allocated SAMPLE, or zero if there was a failure.
	* Not recommended to use this directly. Use OpenSample_OGG instead.
	*/
	SAMPLE* Audio::CreateSample_OGG(const char* fileName)
	{
		SAMPLE* resource 		= 0;
		FILE* fp 				= 0;
		vorbis_info* vorbisInfo = 0;
		OggVorbis_File vorbisFile;
		
		int bytesOfDataRead 	= 0;
		int dataOffset			= 0;
		int bitstream			= 0;
		
		char dataBuffer[AUDIORESOURCE_OGG_BUFFER_SIZE];
		
		///
		fp = fopen(fileName, "rb");
		if (!fp)
		{
			char e[256]; sprintf(e, "Could not load the file %s", fileName); LogFatal(e);
		}
	
		int ovResult = ov_open_callbacks(fp, &vorbisFile, 0, 0, OV_CALLBACKS_DEFAULT);
		if (0 != ovResult)
		{
			switch(ovResult)
			{
				case OV_EREAD:
				{
					LogFatal("ov_open_callbacks Error - A read from media returned an error.");
				} break;
		
				case OV_ENOTVORBIS:
				{
					LogFatal("ov_open_callbacks Error - Bitstream does not contain any Vorbis data.");
				} break;
		
				case OV_EVERSION:
				{
					LogFatal("ov_open_callbacks Error - Vorbis version mismatch.");
				} break;
		
				case OV_EBADHEADER:
				{
					LogFatal("ov_open_callbacks Error - Invalid Vorbis bitstream header.");
				} break;
		
				case OV_EFAULT:
				{
					LogFatal("ov_open_callbacks Error - Internal logic fault; indicates a bug or heap/stack corruption.");
				} break;
			}
			return 0;
		}
	
		vorbisInfo = ov_info(&vorbisFile, -1);
	
		char infoMsg[512];
		sprintf(infoMsg, 
			"\nVorbis Encoder Version: %d\n"
			"Channels: %d\n"
			"Sampling Rate: %d\n"
			"Bitstream Upper Limit: %d\n"
			"Bitstream Lower Limit: %d\n"
			"Bitstream Average Bitrate: %d\n",
			vorbisInfo->version,
			vorbisInfo->channels,
			vorbisInfo->rate,
			vorbisInfo->bitrate_upper,
			vorbisInfo->bitrate_lower,
			vorbisInfo->bitrate_nominal
			);
		LogMessage(infoMsg);
	
		resource = static_cast<SAMPLE*>(malloc(sizeof(SAMPLE)));
		if (!resource)
		{
			LogError("Could not allocate Allegro Audio Sample!");
			ov_clear(&vorbisFile);
			return 0;
		}
		
		resource->bits			= 16;
		resource->stereo 		= (vorbisInfo->channels > 1) ? 1 : 0;
		resource->freq 			= vorbisInfo->rate;
		resource->len 			= ov_pcm_total(&vorbisFile, -1);
		
		resource->data			= malloc(sizeof(unsigned short[resource->len * 0x2]));
		resource->loop_start 	= 0;
		resource->loop_end 		= resource->len;
		resource->priority		= 128;
		
		while((bytesOfDataRead = ov_read(&vorbisFile, 
			dataBuffer, 
			AUDIORESOURCE_OGG_BUFFER_SIZE, 
			0, 
			2, 
			0, 
			&bitstream)))
		{
			unsigned char* dataPointer = static_cast<unsigned char*>(resource->data);
			memcpy(static_cast<unsigned char*>(dataOffset + dataPointer), dataBuffer, bytesOfDataRead);
			dataOffset += bytesOfDataRead;
		}
		
		ov_clear(&vorbisFile);
		
		return resource;
	}
	
	/**************************************************************************/
	
	/**
	* Loads an OGG/Vorbis audio file sample.
	* Do not use this for large audio files, this is for short sound effects.
	* Returns a pointer to an OGG/Vorbis sample resource.
	*/
	AudioSampleResource_OGG* Audio::OpenSample_OGG(const char* fileName)
	{
		AudioSampleResource_OGG* resource = new AudioSampleResource_OGG();
		resource->allegroSample_ = Audio::CreateSample_OGG(fileName);
		return resource;
	}
	
	/**************************************************************************/
	
	/**
	* Releases the memory allocated for an audio sample resource.
	*/
	void Audio::DestroySample_OGG(const AudioSampleResource_OGG* resource)
	{
		Audio::StopSample_OGG(resource);
		destroy_sample(resource->allegroSample_);
		delete resource;
	}
	
	/**************************************************************************/
	
	/**
	* Plays an audio sample resource.
	*/
	int Audio::PlaySample_OGG(const AudioSampleResource_OGG* resource, int volume, int pan, int frequency, int loop)
	{
		return play_sample(resource->allegroSample_, volume, pan, frequency, loop);
	}
	
	/**************************************************************************/
	
	/**
	* Stops the audio sample resource from playing.
	*/
	void Audio::StopSample_OGG(const AudioSampleResource_OGG* resource)
	{
		stop_sample(resource->allegroSample_);
	}
	
	/**************************************************************************/
	
	/**
	* Lets you alter the volume, pan, frequency, and looping status of an
	* audio sample resource while it is playing. If the sample is not playing
	* then this function will do nothing.
	*/
	void Audio::ModifySample_OGG(const AudioSampleResource_OGG* resource, int volume, int pan, int frequency, int loop)
	{
		adjust_sample(resource->allegroSample_, volume, pan, frequency, loop); 
	}

} // end namespace


