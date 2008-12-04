
// CODESTYLE: v2.0

// AnimationSequence.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a list of animation frames

/**
 * \file AnimationSequence.h
 * \brief Animation System Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __ANIMATIONSEQUENCE_H__
#define __ANIMATIONSEQUENCE_H__

#include <vector>

namespace ENGINE
{
	// forward delcare the classes we need
	class AnimationFrame;
	
	/**
	 * \class AnimationSequence
	 * \brief A class to hold a list of animation frames
	 * \ingroup GraphicsGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class AnimationSequence
	{
	public:
		
		/**
		 * default constructor
		 */
		AnimationSequence();
		
		/**
		 * De-allocates any allocated memory by calling AnimationFrame::Destroy()
		 */
		~AnimationSequence();
		
		/**
		 * Adds a frame to the sequence
		 * @param frame is a pointer to a previously allocated AnimationFrame structure
		 */
		void AddFrame(AnimationFrame* frame);
		
		/**
		 * Attempts to set the current frame to \a frameNumber
		 * if \a frameNumber is greater than the number of frames, then the frame will not be changed.
		 * @param frameNumber is the frame ID to try to set the animation with
		 */
		void SetActive(unsigned int frameNumber);
		
		/**
		 * Resets the animation to the first frame
		 */
		void Reset();
		
		/**
		 * Call this to advance the animation frames.\n
		 * frames will only advance if the frame counter is > the current frame's delay time
		 */
		void Update();
		
		/**
		 * Gets the current frame
		 */
		AnimationFrame* GetCurrentFrame();
		
		/**
		 * Gets the frame count
		 * \return the number of frames in the animation sequence
		 */
		unsigned int GetFrameCount();
		
	private:
	
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * \var frames_
		 * \brief an STL vector of pointers to the animation frames that make up this sequence
		 */
		std::vector<AnimationFrame*> frames_;
		
		/**
		 * \var frameCounter_
		 * \brief the amount of time that has passed between now and the last frame change
		 */
		float frameCounter_;
		
		/**
		 * \var currentFrame_
		 * \brief the ID of the active frame
		 */
		unsigned int currentFrame_;
		
	}; // end class

} // end namespace
#endif


