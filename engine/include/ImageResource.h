
// CODESTYLE: v2.0

// ImageResource.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Wraps up Allegro bitmaps

#ifndef __IMAGERESOURCE_H__
#define __IMAGERESOURCE_H__

struct BITMAP;

namespace ENGINE
{
	/**
	* A class to wrap up an Allegro BITMAP structure
	*/
	class ImageResource
	{
	public:
		// public members should be declared here
		ImageResource();
		
		ImageResource(int width, int height, int color = 0);
		
		ImageResource(BITMAP* source = 0);
		
		~ImageResource();
		
		void Create(int width, int height, int color = 0);
		
		void Create(BITMAP* source);
		
		void Destroy();
		
		void SetBitmap(BITMAP* source);
		
		BITMAP* GetBitmap();
		
	private:
		// private members should be declared here
		BITMAP* allegroBitmap_;
	}; // end class

} // end namespace
#endif


