
// CODESTYLE: v2.0

// Audio_OGG.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks - created with help from many source references found on the web and from friends.
// Purpose: These classes wrap the OGG/Vorbis audio resource loading, playback, destruction functionality.

/**
 * \file Audio_OGG.cpp
 * \brief OGG/Vorbis Audio Resource - Implementation
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "Audio_OGG.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	AudioSampleResource_OGG::AudioSampleResource_OGG() :
		allegroSample_(0)
	{
	}
	
	/**************************************************************************/
	
	AudioSampleResource_OGG::~AudioSampleResource_OGG()
	{
		Destroy();
	}
	
	/**************************************************************************/
	
	bool AudioSampleResource_OGG::Load(const char* fileName)
	{
		FILE* fp 				= 0;
		vorbis_info* vorbisInfo = 0;
		OggVorbis_File vorbisFile;
		
		int bytesOfDataRead 	= 0;
		int dataOffset			= 0;
		int bitstream			= 0;
		
		char dataBuffer[AUDIORESOURCE_OGG_BUFFER_SIZE];
		
		fp = fopen(fileName, "rb");
		if (!fp)
		{
			LogFatal("Could not load the file %s", fileName);
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
			return false;
		}
	
		vorbisInfo = ov_info(&vorbisFile, -1);
	
		LogMessage(
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
		
		allegroSample_ = static_cast<SAMPLE*>(malloc(sizeof(SAMPLE)));
		if (0 == allegroSample_)
		{
			LogError("Could not allocate Allegro Audio Sample!");
			ov_clear(&vorbisFile);
			return false;
		}
		
		allegroSample_->bits			= 16;
		allegroSample_->stereo 			= (vorbisInfo->channels > 1) ? 1 : 0;
		allegroSample_->freq 			= vorbisInfo->rate;
		allegroSample_->len 			= ov_pcm_total(&vorbisFile, -1);
		
		allegroSample_->data			= malloc(sizeof(unsigned short[allegroSample_->len * 0x2]));
		allegroSample_->loop_start 		= 0;
		allegroSample_->loop_end 		= allegroSample_->len;
		allegroSample_->priority		= 128;
		
		while((bytesOfDataRead = ov_read(&vorbisFile, 
			dataBuffer, 
			AUDIORESOURCE_OGG_BUFFER_SIZE, 
			0, 
			2, 
			0, 
			&bitstream)))
		{
			unsigned char* dataPointer = static_cast<unsigned char*>(allegroSample_->data);
			memcpy(static_cast<unsigned char*>(dataOffset + dataPointer), dataBuffer, bytesOfDataRead);
			dataOffset += bytesOfDataRead;
		}
		
		ov_clear(&vorbisFile);
		return true;
	}
	
	/**************************************************************************/
	
	int AudioSampleResource_OGG::Play(int volume, int pan, int frequency, int loop)
	{
		return play_sample(allegroSample_, volume, pan, frequency, loop);
	}
	
	/**************************************************************************/
	
	void AudioSampleResource_OGG::Modify(int volume, int pan, int frequency, int loop)
	{
		adjust_sample(allegroSample_, volume, pan, frequency, loop);
	}
	
	/**************************************************************************/
	
	void AudioSampleResource_OGG::Stop()
	{
		stop_sample(allegroSample_);
	}
	
	/**************************************************************************/
	
	void AudioSampleResource_OGG::Destroy()
	{
		Stop();
		if (0 != allegroSample_)
		{
			destroy_sample(allegroSample_);
			allegroSample_ = 0;
		}
	}
	
	/**************************************************************************/
	
	SAMPLE* AudioSampleResource_OGG::GetAllegroSample()
	{
		return allegroSample_;
	}
	
	/**************************************************************************/
	
	AudioStreamResource_OGG::AudioStreamResource_OGG() :
		fileName_(0),
		allegroAudioStream_(0),
		currentBufferPage_(0),
		playingBufferPage_(0),
		stereo_(0),
		frequency_(0),
		bits_(0),
		length_(0),
		loop_(0),
		volume_(0),
		pan_(0),
		stopped_(true)
	{
		memset(&vorbisFile_, 0, sizeof(OggVorbis_File));
	}
	
	AudioStreamResource_OGG::~AudioStreamResource_OGG()
	{
		Destroy();
	}
	
	bool AudioStreamResource_OGG::Load(const char* fileName, int volume, int pan, int loop)
	{
		fileName_ = strdup(fileName);

		if (!fileName_)
		{
			return false;
		}
		
		if (OpenStream())
		{
			Destroy();
			return false;
		}
		
		volume_ = volume;
		pan_ 	= pan;
		loop_ 	= loop;
		
		if (PlayStream())
		{
			Destroy();
			return false;
		}
		
		return true;
	}
	
	/**************************************************************************/
	
	int AudioStreamResource_OGG::Update()
	{
		if (stopped_)
		{
			Restart();
		}
		
		unsigned char* data = static_cast<unsigned char*>(get_audio_stream_buffer(allegroAudioStream_));
		
		if (!data) 
		{
			if (currentBufferPage_ != playingBufferPage_) 
			{
				int read = ReadStreamData();
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
		
		playingBufferPage_++;
		playingBufferPage_ %= AUDIORESOURCE_OGG_BUFFER_PAGES;
		memcpy(data, buffer_[playingBufferPage_], AUDIORESOURCE_OGG_BUFFER_SIZE);
		free_audio_stream_buffer(allegroAudioStream_);
		
		return 1;
	}
	
	/**************************************************************************/
	
	void AudioStreamResource_OGG::Stop()
	{
		stop_audio_stream(allegroAudioStream_);
		for (int index = 0; index < AUDIORESOURCE_OGG_BUFFER_PAGES; index++) 
		{
			free(buffer_[index]);
			buffer_[index] = 0;
		}
		stopped_ = true;
	}
	
	/**************************************************************************/
	
	int AudioStreamResource_OGG::Restart()
	{
		stopped_ = false;
		return PlayStream();
	}
	
	/**************************************************************************/
	
	void AudioStreamResource_OGG::Destroy()
	{
		if (!stopped_)
		{
			Stop();
		}
		
		ov_clear(&vorbisFile_);
		free(fileName_);
	}
	
	/**************************************************************************/
	
	int AudioStreamResource_OGG::OpenStream()
	{
		FILE* fp;
		vorbis_info* vorbisInfo;
		fp = fopen(fileName_, "rb");
		if (!fp)
		{
			LogFatal("Could not load the file %s", fileName_);
		}
	
		int ovResult = ov_open_callbacks(fp, &vorbisFile_, 0, 0, OV_CALLBACKS_DEFAULT);
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
	
		vorbisInfo = ov_info(&vorbisFile_, -1);
	
		LogMessage(
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

		bits_ 		= 16;
		stereo_ 	= (vorbisInfo->channels > 1) ? 1 : 0;
		frequency_ 	= vorbisInfo->rate;
		length_ 	= ov_pcm_total(&vorbisFile_, -1);
		
		return 0;
	}
	
	/**************************************************************************/
	
	int AudioStreamResource_OGG::ReadStreamData()
	{
		int bytesOfDataRead = 0;
		int bitstream = 0;
		int page = currentBufferPage_;
		
		currentBufferPage_++;
		currentBufferPage_ %= AUDIORESOURCE_OGG_BUFFER_PAGES;
		memset(buffer_[page], 0, AUDIORESOURCE_OGG_BUFFER_SIZE);

		while (bytesOfDataRead < AUDIORESOURCE_OGG_BUFFER_SIZE) 
		{
			int thisRead = ov_read(&vorbisFile_, 
				buffer_[page] + bytesOfDataRead,
				AUDIORESOURCE_OGG_BUFFER_SIZE - bytesOfDataRead,
				0, 
				2, 
				0, 
				&bitstream);
				
			if (0 == thisRead) 
			{
				if (loop_) 
				{
					ov_clear(&vorbisFile_);
					if (OpenStream())
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
	
	int AudioStreamResource_OGG::PlayStream()
	{
		currentBufferPage_ 	= 0;
		playingBufferPage_ 	= -1;

		int bitsDiv = static_cast<int>((bits_ / (sizeof(char) * 8)));
		
		int bufferDiv = static_cast<int>(AUDIORESOURCE_OGG_BUFFER_SIZE / (stereo_ ? 2 : 1));
		
		bitsDiv = (bitsDiv <= 0) ? 1 : bitsDiv;
		
		allegroAudioStream_ = play_audio_stream(
			static_cast<int>(bufferDiv / bitsDiv), 
			bits_, 
			stereo_, 
			frequency_, 
			volume_, 
			pan_);

		if (!allegroAudioStream_)
		{
			LogFatal("Failed to create Allegro Audio Stream!");
		}
		
		for (int index = 0; index < AUDIORESOURCE_OGG_BUFFER_PAGES; index++)
		{
			buffer_[index] = static_cast<char*>(malloc(AUDIORESOURCE_OGG_BUFFER_SIZE));
			
			if (!buffer_[index])
			{
				LogError("Could not allocate audio buffer!");
				Destroy();
				return 1;
			}
			
			if (ReadStreamData() < 0) 
			{
				return 1;
			}
		}
		
		stopped_ = false;
		return 0;
	}
	
	
} // end namespace


