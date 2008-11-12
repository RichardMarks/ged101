
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
		allegroBitmap_ = create_bitmap_ex(bitmap_color_depth(screen), width, height);
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
	
	bool Load(const char* fileName)
	{
		Destroy();
		BITMAP* tempBitmap = load_bitmap(fileName, 0);
		if (0 != tempBitmap)
		{
			Create(tempBitmap->w, tempBitmap->h);
			blit(tempBitmap, allegroBitmap_, 0, 0, 0, 0, tempBitmap->w, tempBitmap->h);
			destroy_bitmap(tempBitmap);
			return true;
		}
		
		{ char e[256]; sprintf(e,"Could not load %s!", fileName); LogError(e); }
		return false;
	}
	
	/**************************************************************************/
	
	bool LoadFrom(const char* fileName, int sourceX, int sourceY, int width, int height)
	{
		Destroy();
		BITMAP* tempBitmap = load_bitmap(fileName, 0);
		if (0 != tempBitmap)
		{
			Create(width, height);
			blit(tempBitmap, allegroBitmap_, sourceX, sourceY, 0, 0, width, height);
			destroy_bitmap(tempBitmap);
			return true;
		}
		
		{ char e[256]; sprintf(e,"Could not load %s!", fileName); LogError(e); }
		return false;
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
	
	// blitting
	void Blit(
		ImageResource* destination, 
		int srcX, int srcY,
		int destX, int destY,
		int width, int height)
	{
		blit(allegroBitmap_, destination->GetBitmap(), srcX, srcY, destX, destY, width, height);
	}
	
	/**************************************************************************/
	
	void Blit(
		ImageResource* destination, 
		int srcX, int srcY,
		int srcWidth, int srcHeight,
		int destX, int destY,
		int destWidth, int destHeight)
	{
		stretch_blit(allegroBitmap_, destination->GetBitmap(), srcX, srcY, srcWidth, srcHeight, destX, destY, destWidth, destHeight);
	}
	
	/**************************************************************************/
	
	void BlitMasked(
		ImageResource* destination, 
		int srcX, int srcY,
		int destX, int destY,
		int width, int height)
	{
		masked_blit(allegroBitmap_, destination->GetBitmap(), srcX, srcY, destX, destY, width, height);
	}
	
	/**************************************************************************/
	
	void BlitMasked(
		ImageResource* destination, 
		int srcX, int srcY,
		int srcWidth, int srcHeight,
		int destX, int destY,
		int destWidth, int destHeight)
	{
		masked_stretch_blit(allegroBitmap_, destination->GetBitmap(), srcX, srcY, srcWidth, srcHeight, destX, destY, destWidth, destHeight);
	}
	
	/**************************************************************************/
	
	// transformations
	void Mirror()
	{
		BITMAP* originalCopy = create_bitmap(allegroBitmap_->w, allegroBitmap_->h);
		if (0 != originalCopy)
		{
			blit(allegroBitmap_, originalCopy, 0, 0, 0, 0, allegroBitmap_->w, allegroBitmap_->h);
			draw_sprite_h_flip(allegroBitmap_, originalCopy, 0, 0);
			destroy_bitmap(originalCopy);
		}
	}
	
	/**************************************************************************/
	
	void Flip()
	{
		BITMAP* originalCopy = create_bitmap(allegroBitmap_->w, allegroBitmap_->h);
		if (0 != originalCopy)
		{
			blit(allegroBitmap_, originalCopy, 0, 0, 0, 0, allegroBitmap_->w, allegroBitmap_->h);
			draw_sprite_v_flip(allegroBitmap_, originalCopy, 0, 0);
			destroy_bitmap(originalCopy);
		}
	}
	
	/**************************************************************************/
	
	void Rotate(int angle)
	{
		BITMAP* originalCopy = create_bitmap(allegroBitmap_->w, allegroBitmap_->h);
		if (0 != originalCopy)
		{
			blit(allegroBitmap_, originalCopy, 0, 0, 0, 0, allegroBitmap_->w, allegroBitmap_->h);
			float rotationAngle = 0.711f * static_cast<float>(angle);
			rotate_sprite(allegroBitmap_, originalCopy, 0, 0, itofix(rotationAngle));
			destroy_bitmap(originalCopy);
		}
	}
	
	/**************************************************************************/
	
	// pixel access
	int GetPixel(int x, int y)
	{
		return get_pixel(allegroBitmap_, x, y);
	}
	
	/**************************************************************************/
	
	void SetPixel(int x, int y, int color)
	{
		set_pixel(allegroBitmap_, x, y, color);
	}
	
	/**************************************************************************/
	
	// drawing primitives
	void ImageResource::Line(int x1, int y1, int x2, int y2, int color)
	{
		line(allegroBitmap_, x1, y1, x2, y2, color);
	}
	
	/**************************************************************************/
	
	void ImageResource::Rect(int x1, int y1, int x2, int y2, int color, bool filled)
	{
		if (filled)
		{
			rectfill(allegroBitmap_, x1, y2, x2, y2, color);
		}
		else
		{
			rect(allegroBitmap_, x1, y1, x2, y2, color);
		}
	}
	
	/**************************************************************************/
	
	void ImageResource::Ellipse(int x, int y, int radiusX, int radiusY, int color, bool filled)
	{
		if (filled)
		{
			ellipsefill(allegroBitmap_, x, y, radiusX, radiusY, color);
		}
		else
		{
			ellipse(allegroBitmap_, x, y, radiusX, radiusY, color);
		}
	}
	
	/**************************************************************************/
	
	void ImageResource::Circle(int x, int y, int radius, int color, bool filled)
	{
		if (filled)
		{
			circlefill(allegroBitmap_, x, y, radius, color);
		}
		else
		{
			circle(allegroBitmap_, x, y, radius, color);
		}
	}
	
	/**************************************************************************/
	
	void ImageResource::Arc(int x, int y, int radius, int startAngle, int endAngle, int color)
	{
		float start = 0.711f * static_cast<float>(startAngle);
		float end = 0.711f * static_cast<float>(endAngle);
		arc(allegroBitmap_, x, y, itofix(start), itofix(end), radius, color);
	}
	
	/**************************************************************************/
	
	void ImageResource::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, bool filled)
	{
		if (filled)
		{
			triangle(allegroBitmap_, x1, y1, x2, y2, x3, y3, color);
		}
		else
		{
			Line(x1, y1, x2, y2, color);
			Line(x2, y2, x3, y3, color);
			Line(x3, y3, x1, y1, color);
		}
	}
	
	/**************************************************************************/
	
	void ImageResource::Fill(int x, int y, int color)
	{
		floodfill(allegroBitmap_, x, y, color);
	}
	
	/**************************************************************************/
	
	// utility
	void ImageResource::Clear(int color)
	{
		clear_to_color(allegroBitmap_, color);
	}
	
	/**************************************************************************/
	
	void ImageResource::Save(const char* fileName)
	{
		save_bitmap(fileName, allegroBitmap_, 0);
	}
	
	/**************************************************************************/
	
	BITMAP* ImageResource::GetBitmap()
	{
		return allegroBitmap_;
	}

} // end namespace


