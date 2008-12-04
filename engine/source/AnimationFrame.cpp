
// CODESTYLE: v2.0

// AnimationFrame.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a single frame of animation data

/**
 * \file AnimationFrame.cpp
 * \brief Animation System Module - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "AnimationFrame.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	AnimationFrame::AnimationFrame() :
		image_(0),
		frameDelay_(0.0f)
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	AnimationFrame::AnimationFrame(ImageResource* image, float frameDelay)
	{
		image_ = new ImageResource(image->GetBitmap());
		frameDelay_ = frameDelay;
	}
	
	/**************************************************************************/
	
	AnimationFrame::~AnimationFrame()
	{
		// implement class destructor here
		Destroy();
	} // end destructor
	
	/**************************************************************************/
	
	void AnimationFrame::SetImage(ImageResource* image)
	{
		Destroy();
		image_ = new ImageResource(image->GetBitmap());
	}
	
	/**************************************************************************/
	
	void AnimationFrame::SetDelay(float frameDelay)
	{
		frameDelay_ = frameDelay;
	}
	
	/**************************************************************************/
	
	ImageResource* AnimationFrame::GetImage()
	{
		return image_;
	}
	
	/**************************************************************************/
	
	float AnimationFrame::GetDelay()
	{
		return frameDelay_;
	}
	
	/**************************************************************************/
	
	void AnimationFrame::Destroy()
	{
		if (0 != image_)
		{
			delete image_;
		}
	}

} // end namespace


