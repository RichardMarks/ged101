
// CODESTYLE: v2.0

// Image.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Wraps up common operations to perform on images

#ifndef __IMAGE_H__
#define __IMAGE_H__

namespace ENGINE
{
	class ImageResource;
	class Image
	{
	public:
		
		// creation
		
		static ImageResource* Create(int width, int height, int color = 0);
		static ImageResource* Load(const char* fileName);
		
		// destruction
		
		static void Destroy(ImageResource* resource);
		
		// blitting
		
		static void Blit(
			ImageResource* source, 
			ImageResource* destination, 
			int srcX, int srcY,
			int destX, int destY,
			int width, int height);
			
		static void Blit(
			ImageResource* source, 
			ImageResource* destination, 
			int srcX, int srcY,
			int srcWidth, int srcHeight,
			int destX, int destY,
			int destWidth, int destHeight);
		
		static void BlitMasked(
			ImageResource* source, 
			ImageResource* destination, 
			int srcX, int srcY,
			int destX, int destY,
			int width, int height);
			
		static void BlitMasked(
			ImageResource* source, 
			ImageResource* destination, 
			int srcX, int srcY,
			int srcWidth, int srcHeight,
			int destX, int destY,
			int destWidth, int destHeight);
			
		static void BlitMirrored(
			ImageResource* source,
			ImageResource* destination,
			int destX, int destY);
			
		static void BlitFlipped(
			ImageResource* source,
			ImageResource* destination,
			int destX, int destY);
		
		// transforming
		static void Mirror(ImageResource* resource);
		static void Flip(ImageResource* resource);
		static void Rotate(ImageResource* resource, int angle);
		
		// pixel access
		static int GetPixel(ImageResource* resource, int x, int y);
		static void SetPixel(ImageResource* resource, int x, int y, int color);
		
	private:
		// private members should be declared here
		
		/**
		* The class constructor is private because this is just a wrapper class
		* and should not ever have an instance created.
		*/
		Image();
		
		/**
		* The copy constructor and assignment operator are private as well.
		*/
		Image(const Image& rhs);
		Image& operator=(const Image& rhs);
	};

} // end namespace
#endif


