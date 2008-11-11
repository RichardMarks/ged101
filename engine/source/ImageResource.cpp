
// CODESTYLE: v2.0

// ImageResource.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Wraps up Allegro bitmaps

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	ImageResource::ImageResource() :
		allegroBitmap_(0)
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	ImageResource::ImageResource(int width, int height, int color)
	{
		allegroBitmap_ = 0;
		Create(width, height, color);
	}
	
	/**************************************************************************/
	
	ImageResource::ImageResource(BITMAP* source)
	{
		allegroBitmap_ = 0;
		Create(source);
	}
	
	/**************************************************************************/
	
	ImageResource::~ImageResource()
	{
		// implement class destructor here
		Destroy();
	} // end destructor
	
	/**************************************************************************/
	
	void ImageResource::Create(int width, int height, int color)
	{
		Destroy();
		allegroBitmap_ = create_bitmap(width, height);
		if (0 == allegroBitmap_)
		{
			LogError("Could not create the ImageResource!");
		}
		clear_to_color(allegroBitmap_, color);
	}
	
	/**************************************************************************/
	
	void ImageResource::Create(BITMAP* source)
	{
		Destroy();
		allegroBitmap_ = source;
	}
	
	/**************************************************************************/
	
	void ImageResource::Destroy()
	{
		if (0 != allegroBitmap_)
		{
			destroy_bitmap(allegroBitmap_);
			allegroBitmap_ = 0;
		}
	}
	
	/**************************************************************************/
	
	void ImageResource::SetBitmap(BITMAP* source)
	{
		Destroy();
		allegroBitmap_ = source;
	}
	
	/**************************************************************************/
	
	BITMAP* ImageResource::GetBitmap()
	{
		return allegroBitmap_;
	}

} // end namespace


