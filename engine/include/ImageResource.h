
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
		
		// creation
		void Create(int width, int height, int color = 0);
		
		void Create(BITMAP* source);
		
		bool Load(const char* fileName);
		
		bool LoadFrom(const char* fileName, int sourceX, int sourceY, int width, int height);
		
		// destruction
		void Destroy();
		
		// blitting
		void Blit(
			ImageResource* destination, 
			int srcX, int srcY,
			int destX, int destY,
			int width, int height);
		
		void Blit(
			ImageResource* destination, 
			int srcX, int srcY,
			int srcWidth, int srcHeight,
			int destX, int destY,
			int destWidth, int destHeight);
			
		void BlitMasked(
			ImageResource* destination, 
			int srcX, int srcY,
			int destX, int destY,
			int width, int height);
		
		void BlitMasked(
			ImageResource* destination, 
			int srcX, int srcY,
			int srcWidth, int srcHeight,
			int destX, int destY,
			int destWidth, int destHeight);
		
		// transformations
		void Mirror();
		void Flip();
		void Rotate(int angle);
		
		// pixel access
		int GetPixel(int x, int y);
		void SetPixel(int x, int y, int color);
		
		// drawing primitives
		void Draw(const char* drawString);
		void Line(int x1, int y1, int x2, int y2, int color);
		void Rect(int x1, int y1, int x2, int y2, int color, bool filled = false);
		void Ellipse(int x, int y, int radiusX, int radiusY, int color, bool filled = false);
		void Circle(int x, int y, int radius, int color, bool filled = false);
		void Arc(int x, int y, int radius, int startAngle, int endAngle, int color);
		void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, bool filled = false);
		void Fill(int x, int y, int color);
		
		// utility
		void Clear(int color = 0);
		void Save(const char* fileName);
		
		// member accessor
		BITMAP* GetBitmap();
		
	private:
		// private members should be declared here
		BITMAP* LoadBitmapInternal(const char* fileName);
		BITMAP* LoadPNGInternal(const char* fileName);
		BITMAP* allegroBitmap_;
	}; // end class

} // end namespace
#endif


