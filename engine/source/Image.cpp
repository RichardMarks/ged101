
// CODESTYLE: v2.0

// Image.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Wraps up common operations to perform on images

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "Image.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	// creation
		
	ImageResource* Image::Create(int width, int height, int color)
	{
	}
	
	/**************************************************************************/
	
	ImageResource* Image::Load(const char* fileName)
	{
	}
	
	/**************************************************************************/
	
	// destruction
	
	void Image::Destroy(ImageResource* resource)
	{
	}
	
	/**************************************************************************/
	
	// blitting
	
	void Image::Blit(
		ImageResource* source, 
		ImageResource* destination, 
		int srcX, int srcY,
		int destX, int destY,
		int width, int height)
	{
	}
	
	/**************************************************************************/
	
	void Image::Blit(
		ImageResource* source, 
		ImageResource* destination, 
		int srcX, int srcY,
		int srcWidth, int srcHeight,
		int destX, int destY,
		int destWidth, int destHeight)
	{
	}
	
	/**************************************************************************/
	
	void Image::BlitMasked(
		ImageResource* source, 
		ImageResource* destination, 
		int srcX, int srcY,
		int destX, int destY,
		int width, int height)
	{
	}
	
	/**************************************************************************/
	
	void Image::BlitMasked(
		ImageResource* source, 
		ImageResource* destination, 
		int srcX, int srcY,
		int srcWidth, int srcHeight,
		int destX, int destY,
		int destWidth, int destHeight)
	{
	}
	
	/**************************************************************************/
	
	void Image::BlitMirrored(
		ImageResource* source,
		ImageResource* destination,
		int destX, int destY)
	{
	}
	
	/**************************************************************************/
	
	void Image::BlitFlipped(
		ImageResource* source,
		ImageResource* destination,
		int destX, int destY)
	{
	}
	
	/**************************************************************************/
	
	// transforming
	void Image::Mirror(ImageResource* resource)
	{
	}
	
	/**************************************************************************/
	
	void Image::Flip(ImageResource* resource)
	{
	}
	
	/**************************************************************************/
	
	void Image::Rotate(ImageResource* resource, int angle)
	{
	}
	
	/**************************************************************************/
	
	// pixel access
	int Image::GetPixel(ImageResource* resource, int x, int y)
	{
	}
	
	/**************************************************************************/
	
	void Image::SetPixel(ImageResource* resource, int x, int y, int color)
	{
	}
	
} // end namespace


