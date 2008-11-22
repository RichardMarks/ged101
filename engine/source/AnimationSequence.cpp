
// CODESTYLE: v2.0

// AnimationSequence.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a list of animation frames

/**
 * \file AnimationSequence.cpp
 * \brief Animation System Module - Implementation
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "AnimationSequence.h"

// include the animation frame header
#include "AnimationFrame.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	AnimationSequence::AnimationSequence() :
		frameCounter_(0.0f),
		currentFrame_(0)
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	AnimationSequence::~AnimationSequence()
	{
		// implement class destructor here
	} // end destructor
	
	/**************************************************************************/
	
	void AnimationSequence::AddFrame(AnimationFrame* frame)
	{
		frames_.push_back(frame);
	}
	
	/**************************************************************************/
	
	void AnimationSequence::SetActive(unsigned int frameNumber)
	{
		currentFrame_ = (frameNumber > frames_.size()) ? 0 : frameNumber;
	}
	
	/**************************************************************************/
	
	void AnimationSequence::Reset()
	{
		currentFrame_ = 0;
		frameCounter_ = 0.0f;
	}
	
	/**************************************************************************/
	
	void AnimationSequence::Update()
	{
		frameCounter_ += 1.0f;
		
		if (frameCounter_ >= frames_.at(currentFrame_)->GetDelay())
		{
			if (++currentFrame_ >= frames_.size())
			{
				currentFrame_ = 0;
			}
			frameCounter_ = 0.0f;
		}
	}
	
	/**************************************************************************/
	
	AnimationFrame* AnimationSequence::GetCurrentFrame()
	{
		return frames_.at(currentFrame_);
	}
	
	/**************************************************************************/
	
	unsigned int AnimationSequence::GetFrameCount()
	{
		return static_cast<unsigned int>(frames_.size());
	}
	
	/**************************************************************************/
	
	void AnimationSequence::Destroy()
	{
		// delete all frames
		unsigned int index = 0;
		for (index = 0; index < frames_.size(); index++)
		{
			if (0 != frames_[index])
			{
				delete frames_[index];
				frames_[index] = 0;
			}
		}
		frames_.clear();
	}

} // end namespace


