
// CODESTYLE: v2.0

// AnimationFrame.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a single frame of animation data

/**
 * \file AnimationFrame.h
 * \brief Animation System Module - Header
 */

#ifndef __ANIMATIONFRAME_H__
#define __ANIMATIONFRAME_H__

namespace ENGINE
{
	// forward delcare the classes we need
	class ImageResource;
	
	/**
	 * \class AnimationFrame
	 * \brief A class to hold a single frame of animation data
	 */
	class AnimationFrame
	{
	public:
		
		/**
		 * default constructor
		 */
		AnimationFrame();
		
		/**
		 * alternate constructor
		 * @param image is a pointer to an ImageResource that holds the image data for the animation frame.
		 * @param frameDelay is the amount of time that needs to pass before the frame will be considered old and be updated.
		 */
		AnimationFrame(ImageResource* image, float frameDelay);
		
		/**
		 * De-allocates any allocated memory by calling AnimationFrame::Destroy()
		 */
		~AnimationFrame();
		
		/**
		 * Sets the animation frame image
		 * @param image is a pointer to an ImageResource that holds the image data for the animation frame.
		 */
		void SetImage(ImageResource* image);
		
		/**
		 * Sets the animation frame delay time
		 * @param frameDelay is the amount of time that needs to pass before the frame will be considered old and be updated.
		 */
		void SetDelay(float frameDelay);
		
		/**
		 * Gets the animation frame image
		 * \return a pointer to an ImageResource that holds the image data for the animation frame.
		 */
		ImageResource* GetImage();
		
		/**
		 * Gets the animation frame delay time
		 * \return the amount of time that needs to pass before the frame will be considered old and be updated.
		 */
		float GetDelay();
		
	private:
	
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * \var image_
		 * \brief a pointer to an ImageResource that holds the image data for the animation frame.
		 */
		ImageResource* image_;
		
		/**
		 * \var frameDelay_
		 * \brief the amount of time that needs to pass before the frame will be considered old and be updated.
		 */
		float frameDelay_;
	}; // end class

} // end namespace
#endif


