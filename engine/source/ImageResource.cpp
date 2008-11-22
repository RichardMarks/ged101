
// CODESTYLE: v2.0

// ImageResource.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class for loading, saving, manipulating, and rendering non-animated bitmap images

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include the libpng header
#include <png.h>

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
	
	bool ImageResource::Load(const char* fileName)
	{
		Destroy();
		
		BITMAP* tempBitmap = 0;
		char fileExt[4]; 
		int fileNameLen = strlen(fileName);
		fileExt[0] = fileName[fileNameLen - 3];
		fileExt[1] = fileName[fileNameLen - 2];
		fileExt[2] = fileName[fileNameLen - 1];
		fileExt[3] = '\0';
		
		if (!stricmp(fileExt, "png") || !stricmp(fileExt, "PNG"))
		{
			tempBitmap = LoadPNGInternal(fileName);
		}
		else
		{
			tempBitmap = LoadBitmapInternal(fileName);
		}
		
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
	
	bool ImageResource::LoadFrom(const char* fileName, int sourceX, int sourceY, int width, int height)
	{
		Destroy();
		
		BITMAP* tempBitmap = 0;
		char fileExt[4]; 
		int fileNameLen = strlen(fileName);
		fileExt[0] = fileName[fileNameLen - 3];
		fileExt[1] = fileName[fileNameLen - 2];
		fileExt[2] = fileName[fileNameLen - 1];
		fileExt[3] = '\0';
		
		if (!stricmp(fileExt, "png") || !stricmp(fileExt, "PNG"))
		{
			tempBitmap = LoadPNGInternal(fileName);
		}
		else
		{
			tempBitmap = LoadBitmapInternal(fileName);
		}
		
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
			// if the bitmap is the allegro screen bitmap, then we do not destroy it!
			if (screen == allegroBitmap_)
			{
				allegroBitmap_ = 0;
				return;
			}
			
			destroy_bitmap(allegroBitmap_);
			allegroBitmap_ = 0;
		}
	}
	
	/**************************************************************************/
	
	// blitting
	void ImageResource::Blit(
		ImageResource* destination, 
		int srcX, int srcY,
		int destX, int destY,
		int width, int height)
	{
		blit(allegroBitmap_, destination->GetBitmap(), srcX, srcY, destX, destY, width, height);
	}
	
	/**************************************************************************/
	
	void ImageResource::Blit(
		ImageResource* destination, 
		int srcX, int srcY,
		int srcWidth, int srcHeight,
		int destX, int destY,
		int destWidth, int destHeight)
	{
		stretch_blit(allegroBitmap_, destination->GetBitmap(), srcX, srcY, srcWidth, srcHeight, destX, destY, destWidth, destHeight);
	}
	
	/**************************************************************************/
	
	void ImageResource::BlitMasked(
		ImageResource* destination, 
		int srcX, int srcY,
		int destX, int destY,
		int width, int height)
	{
		masked_blit(allegroBitmap_, destination->GetBitmap(), srcX, srcY, destX, destY, width, height);
	}
	
	/**************************************************************************/
	
	void ImageResource::BlitMasked(
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
	void ImageResource::Mirror()
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
	
	void ImageResource::Flip()
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
	
	void ImageResource::Rotate(int angle)
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
	int ImageResource::GetPixel(int x, int y)
	{
		return getpixel(allegroBitmap_, x, y);
	}
	
	/**************************************************************************/
	
	void ImageResource::SetPixel(int x, int y, int color)
	{
		putpixel(allegroBitmap_, x, y, color);
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
	
	BITMAP* ImageResource::LoadBitmapInternal(const char* fileName)
	{
		return load_bitmap(fileName, 0);
	}
	
	/**************************************************************************/
	
	BITMAP* ImageResource::LoadPNGInternal(const char* fileName)
	{
		FILE* fp = fopen(fileName, "rb");
		if (fp)
		{
			// read header
			unsigned char pngHeader[8];
			fread(&pngHeader, sizeof(unsigned char), 8, fp);
			if (0 != png_sig_cmp(pngHeader, 0, 8))
			{
				fclose(fp);
				{ char e[256]; sprintf(e, "%s is not a valid PNG file!", fileName); LogFatal(e); }
			}
			
			// create the png structures we need for reading
			// it is not apparent, but these are all pointers
			// can thank the idiots that made libpng for the shit typedef names
			png_structp pngReadStruct;
			png_infop 	pngInfoStruct;
			png_infop 	pngEndStruct;
			
			pngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
			if (!pngReadStruct)
			{
				fclose(fp);
				LogFatal("Cannot create the PNG Read Structure!");
			}
			
			pngInfoStruct = png_create_info_struct(pngReadStruct);
			if (!pngInfoStruct)
			{
				fclose(fp);
				png_destroy_read_struct(&pngReadStruct, 0, 0);
				LogFatal("Cannot create the PNG Info Structure!");
			}
			
			pngEndStruct = png_create_info_struct(pngReadStruct);
			if (!pngEndStruct)
			{
				fclose(fp);
				png_destroy_read_struct(&pngReadStruct, &pngInfoStruct, 0);
				LogFatal("Cannot create the PNG Info Structure!");
			}

			png_init_io(pngReadStruct, fp);
			png_set_sig_bytes(pngReadStruct, 8);
			
			// read dimensions
			unsigned long imageWidth = 0;
			unsigned long imageHeight = 0;
			int imageBitsPerPixel = 0;
			int imageColorType = 0;
			
			png_read_info(pngReadStruct, pngInfoStruct);
			png_get_IHDR(pngReadStruct, 
				pngInfoStruct, 
				&imageWidth, 
				&imageHeight, 
				&imageBitsPerPixel,
				&imageColorType,
				0,
				0,
				0);
			
			png_set_packing(pngReadStruct);
			
			// expand low-bpp gray-scale to 8 bit
			if ((imageColorType == PNG_COLOR_TYPE_GRAY) && (imageBitsPerPixel < 8))
			{
				png_set_expand(pngReadStruct);
			}
			
			// convert gray-scale to RGB
			if ((imageColorType == PNG_COLOR_TYPE_GRAY) || (imageColorType == PNG_COLOR_TYPE_GRAY_ALPHA))
			{
				png_set_gray_to_rgb(pngReadStruct);
			}
			
			// if there is transparency info, then create an alpha channel
			bool transparencyToAlpha = false;
			if (png_get_valid(pngReadStruct, pngInfoStruct, PNG_INFO_tRNS))
			{
				png_set_tRNS_to_alpha(pngReadStruct);
				transparencyToAlpha = true;
			}
			
			// convert 16 bit to 8 bit
			if (16 == imageBitsPerPixel)
			{
				png_set_strip_16(pngReadStruct);
			}

			// read pixels
			unsigned long imageBytesPerRow = png_get_rowbytes(pngReadStruct, pngInfoStruct);
			
			imageBitsPerPixel = imageBytesPerRow * 8 / imageWidth;
			
			imageBitsPerPixel = (imageBitsPerPixel < 8) ? 8 : imageBitsPerPixel;
			
			BITMAP* resource = 0;
			resource = create_bitmap_ex(imageBitsPerPixel, imageWidth, imageHeight);
			if (0 == resource)
			{
				png_read_end(pngReadStruct, pngEndStruct);
				png_destroy_read_struct(&pngReadStruct, &pngInfoStruct, &pngEndStruct);
				fclose(fp);
				LogFatal("Could not create the Allegro bitmap surface!");
			}
			
			int scanPasses = png_set_interlace_handling(pngReadStruct);
			
			if ((24 == imageBitsPerPixel) || (32 == imageBitsPerPixel)) 
			{
				int c = makecol_depth(imageBitsPerPixel, 0, 0, 255);
				unsigned char *pc = (unsigned char *)&c;
				if (pc[0] == 255)
				{
					png_set_bgr(pngReadStruct);
				}
#if defined(ALLEGRO_BIG_ENDIAN)
				png_set_swap_alpha(pngReadStruct);
#endif	    
			}
			
			for (unsigned long y = 0; y < imageHeight; y++)
			{
				png_read_row(pngReadStruct, resource->line[y], 0);
			}

			png_read_end(pngReadStruct, pngEndStruct);
			png_destroy_read_struct(&pngReadStruct, &pngInfoStruct, &pngEndStruct);
			fclose(fp);
			return resource;
		}
		else
		{
			{ char e[256]; sprintf(e, "Could not open %s!", fileName); LogFatal(e); }
		}
		return 0;
	}
	
	/**************************************************************************/
	
	BITMAP* ImageResource::GetBitmap()
	{
		return allegroBitmap_;
	}
	
	/**************************************************************************/
	
	int ImageResource::GetWidth()
	{
		return allegroBitmap_->w;
	}
	
	/**************************************************************************/
	
	int ImageResource::GetHeight()
	{
		return allegroBitmap_->h;
	}

} // end namespace


