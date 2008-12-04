
// CODESTYLE: v2.0

// ImageResource.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class for loading, saving, manipulating, and rendering non-animated bitmap images

/**
 * \file ImageResource.h
 * \brief Bitmap Image Resource Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __IMAGERESOURCE_H__
#define __IMAGERESOURCE_H__

struct BITMAP;

namespace ENGINE
{
	/**
	 * \class ImageResource
	 * \brief A class for loading, saving, manipulating, and rendering non-animated bitmap images
	 * \ingroup GraphicsGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 *
	 * This class has support for loading images from PNG files, and performing basic transformations such as
	 * rotation, scaling, and flip/mirroring.
	 */
	class ImageResource
	{
	public:
		/**
		 * default constructor
		 */
		ImageResource();
		
		/**
		 * alternate constructor, lets you create a new image of a specified size and color
		 * @param width is the width of the new image in pixels.
		 * @param height is the height of the new image in pixels.
		 * @param color is the color to fill the new image with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		ImageResource(int width, int height, int color = 0);
		
		/**
		 * alternate constructor, lets you create a new image by copying an Allegro BITMAP as a source.
		 * @param source is an Allegro BITMAP pointer to an image to copy from.
		 */
		ImageResource(BITMAP* source);
		
		/**
		 * alternate constructor
		 * Loads an image from a file.
		 * @param fileName is the name of the file that holds the image to be loaded.
		 */
		ImageResource(const char* fileName);
		
		/**
		 * alternate constructor
		 * Loads an image from a spritesheet-style image file using the specified coordinates and 
		 * dimension to rip a rectangular portion of the image that is in the file.
		 * @param fileName is the name of the file that holds the image to be loaded.
		 * @param sourceX is the X coordinate in pixels or the upper-left corner of the source rectangle to rip from.
		 * @param sourceY is the Y coordinate in pixels of the upper-left corner of the source rectangle to rip from.
		 * @param width is the width in pixels of the image to rip.
		 * @param height is the height in pixels of the image to rip.
		 */
		ImageResource(const char* fileName, int sourceX, int sourceY, int width, int height);
		
		/**
		 * destructor calls Destroy to release allocated memory
		 */
		~ImageResource();
		
		// creation
		
		/**
		 * Create a new image of a specified size and color.
		 * @param width is the width of the new image in pixels.
		 * @param height is the height of the new image in pixels.
		 * @param color is the color to fill the new image with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		void Create(int width, int height, int color = 0);
		
		/**
		 * Create a new image by copying an Allegro BITMAP as a source.
		 * @param source is an Allegro BITMAP pointer to an image to copy from.
		 */
		void Create(BITMAP* source);
		
		/**
		 * Loads an image from a file.
		 * @param fileName is the name of the file that holds the image to be loaded.
		 */
		bool Load(const char* fileName);
		
		/**
		 * Loads an image from a spritesheet-style image file using the specified coordinates and 
		 * dimension to rip a rectangular portion of the image that is in the file.
		 * @param fileName is the name of the file that holds the image to be loaded.
		 * @param sourceX is the X coordinate in pixels or the upper-left corner of the source rectangle to rip from.
		 * @param sourceY is the Y coordinate in pixels of the upper-left corner of the source rectangle to rip from.
		 * @param width is the width in pixels of the image to rip.
		 * @param height is the height in pixels of the image to rip.
		 */
		bool Load(const char* fileName, int sourceX, int sourceY, int width, int height);
		
		// blitting
		
		/**
		 * Blits (draws) the image onto another image at the specified location, size, and source.
		 * @param destination is a pointer to an ImageResource that you wish to draw on.
		 * @param srcX is the X coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param srcY is the Y coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param destX is the X coordinate in pixels to draw to on the destination image.
		 * @param destY is the Y coordinate in pixels to draw to on the destination image.
		 * @param width is the width in pixels of the image to draw. Never should be larger than the image's width.
		 * @param height is the height in pixels of the image to draw. Never should be larger than the image's height.
		 */
		void Blit(
			ImageResource* destination, 
			int srcX, int srcY,
			int destX, int destY,
			int width, int height);
		
		/**
		 * Blits (draws) the image onto another image at the specified location, size, and source.
		 * The image will be stretched to fit the destination size.
		 * @param destination is a pointer to an ImageResource that you wish to draw on.
		 * @param srcX is the X coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param srcY is the Y coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param srcWidth is the width in pixels of the image to draw. Never should be larger than the image's width.
		 * @param srcHeight is the height in pixels of the image to draw. Never should be larger than the image's height.
		 * @param destX is the X coordinate in pixels to draw to on the destination image.
		 * @param destY is the Y coordinate in pixels to draw to on the destination image.
		 * @param destWidth is the width in pixels of the desired image to draw.
		 * @param destHeight is the height in pixels of the desired image to draw.
		 */
		void Blit(
			ImageResource* destination, 
			int srcX, int srcY,
			int srcWidth, int srcHeight,
			int destX, int destY,
			int destWidth, int destHeight);
		
		/**
		 * Blits (draws) the image onto another image at the specified location, size, and source.
		 * Any pixels that are colored Magic Pink (255 red, 0 green, 255 blue) #FF00FF in the image are ignored.
		 * This lets you draw an image on top of another image with some areas being specified as DO-NOT-DRAW.
		 * @param destination is a pointer to an ImageResource that you wish to draw on.
		 * @param srcX is the X coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param srcY is the Y coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param destX is the X coordinate in pixels to draw to on the destination image.
		 * @param destY is the Y coordinate in pixels to draw to on the destination image.
		 * @param width is the width in pixels of the image to draw. Never should be larger than the image's width.
		 * @param height is the height in pixels of the image to draw. Never should be larger than the image's height.
		 */
		void BlitMasked(
			ImageResource* destination, 
			int srcX, int srcY,
			int destX, int destY,
			int width, int height);
		
		/**
		 * Blits (draws) the image onto another image at the specified location, size, and source.
		 * The image will be stretched to fit the destination size.
		 * Any pixels that are colored Magic Pink (255 red, 0 green, 255 blue) #FF00FF in the image are ignored.
		 * This lets you draw an image on top of another image with some areas being specified as DO-NOT-DRAW.
		 * @param destination is a pointer to an ImageResource that you wish to draw on.
		 * @param srcX is the X coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param srcY is the Y coordinate in pixels to copy from the image. Most commonly this will be zero.
		 * @param srcWidth is the width in pixels of the image to draw. Never should be larger than the image's width.
		 * @param srcHeight is the height in pixels of the image to draw. Never should be larger than the image's height.
		 * @param destX is the X coordinate in pixels to draw to on the destination image.
		 * @param destY is the Y coordinate in pixels to draw to on the destination image.
		 * @param destWidth is the width in pixels of the desired image to draw.
		 * @param destHeight is the height in pixels of the desired image to draw.
		 */
		void BlitMasked(
			ImageResource* destination, 
			int srcX, int srcY,
			int srcWidth, int srcHeight,
			int destX, int destY,
			int destWidth, int destHeight);
		
		/**
		 * Blits (draws) the image onto another image at the specified location.
		 * Any pixels that are colored Magic Pink (255 red, 0 green, 255 blue) #FF00FF in the image are ignored.
		 * This lets you draw an image on top of another image with some areas being specified as DO-NOT-DRAW.
		 * @param destination is a pointer to an ImageResource that you wish to draw on.
		 * @param destX is the X coordinate in pixels to draw to on the destination image.
		 * @param destY is the Y coordinate in pixels to draw to on the destination image.
		 */
		void SpriteBlit(ImageResource* destination, int destX, int destY);
		
		/**
		 * Blits (draws) the image onto another image at the specified location.
		 * You can specify an alpha value to create a translucency effect.
		 * Any pixels that are colored Magic Pink (255 red, 0 green, 255 blue) #FF00FF in the image are ignored.
		 * This lets you draw an image on top of another image with some areas being specified as DO-NOT-DRAW.
		 * @param destination is a pointer to an ImageResource that you wish to draw on.
		 * @param destX is the X coordinate in pixels to draw to on the destination image.
		 * @param destY is the Y coordinate in pixels to draw to on the destination image.
		 * @param alpha is the alpha value, which should be from 0.0f (invisible) to 1.0f (solid) -- default is 0.5f which is about 50% translucent
		 */
		void AlphaBlit(ImageResource* destination, int destX, int destY, float alpha = 0.5f);
		
		// transformations
		
		/**
		 * Mirrors (flip horizontally) the image
		 */
		void Mirror();
		
		/**
		 * Flips (flip vertically) the image
		 */
		void Flip();
		
		/**
		 * Rotates the image to an arbitrary angle.\n
		 * The rotation is clockwise starting from 0 degrees pointing straight up.
		 * @param angle is the angle in degrees to rotate the image to. This can be an integer value of 0 to 359.
		 */
		void Rotate(int angle);
		
		// pixel access
		
		/**
		 * \return the color of the pixel at the specified coordinate.
		 * @param x is the X coordinate in pixels to get the color from.
		 * @param y is the Y coordinate in pixels to get the color from.
		 */
		int GetPixel(int x, int y);
		
		/**
		 * sets the color of a single pixel at the specified coordinate.
		 * @param x is the X coordinate in pixels at which to set the color.
		 * @param y is the Y coordinate in pixels at which to set the color.
		 * @param color is the color to set the pixel with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		void SetPixel(int x, int y, int color);
		
		// drawing primitives
		
		/**
		 * Draws a line from point (x1, y1) to point (x2, y2) in the specified color.
		 * @param x1 is the X coordinate of the starting point in pixels.
		 * @param y1 is the Y coordinate of the starting point in pixels.
		 * @param x2 is the X coordinate of the ending point in pixels.
		 * @param y2 is the Y coordinate of the ending point in pixels.
		 * @param color is the color to draw the line with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		void Line(int x1, int y1, int x2, int y2, int color);
		
		/**
		 * Draws a rectangle whose upper-left corner is at point (x1, y1) and lower-right corner is at point (x2, y2) in the specified color.\n
		 * The rectangle can also be drawn filled with the color by specifying true for the \a filled parameter.
		 * @param x1 is the X coordinate of the upper-left corner point in pixels.
		 * @param y1 is the Y coordinate of the upper-left point in pixels.
		 * @param x2 is the X coordinate of the lower-right point in pixels.
		 * @param y2 is the Y coordinate of the lower-right point in pixels.
		 * @param color is the color to draw the rectangle with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 * @param filled specifies if the rectangle should be filled with color or drawn as a wireframe. Can be true or false. Default value is false.
		 */
		void Rect(int x1, int y1, int x2, int y2, int color, bool filled = false);
		
		/**
		 * Draws a rectangle filled with a linear interpolated gradient from 4 colored corners.
		 * This should not be used in a real-time loop, but rather to generate gradients to be stored and used later.
		 * @param x1 is the X coordinate of the upper-left corner point in pixels.
		 * @param y1 is the Y coordinate of the upper-left point in pixels.
		 * @param x2 is the X coordinate of the lower-right point in pixels.
		 * @param y2 is the Y coordinate of the lower-right point in pixels.
		 * @param c1 is the color for the upper-left corner of the rectangle.
		 * @param c2 is the color for the upper-right corner of the rectangle.
		 * @param c3 is the color for the lower-left corner of the rectangle.
		 * @param c4 is the color for the lower-right corner of the rectangle.
		 */
		void GradientRect(int x1, int y1, int x2, int y2, int c1, int c2, int c3, int c4);
		
		/**
		 * Draws an ellipse that fits inside a rectangle whose upper-left corner is at point (x, y) 
		 * and lower-right corner is at point (x + 2*radiusX, y + 2*radiusY) in the specified color.\n
		 * The ellipse can also be drawn filled with the color by specifying true for the \a filled parameter.
		 * @param x is the X coordinate of the upper-left corner point in pixels.
		 * @param y is the Y coordinate of the upper-left point in pixels.
		 * @param radiusX is the radius in pixels of the ellipse along the X axis.
		 * @param radiusY is the radius in pixels of the ellipse along the Y axis.
		 * @param color is the color to draw the ellipse with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 * @param filled specifies if the ellipse should be filled with color or drawn as a wireframe. Can be true or false. Default value is false.
		 */
		void Ellipse(int x, int y, int radiusX, int radiusY, int color, bool filled = false);
		
		/**
		 * Draws a circle of the specified radius, in the specified color on the image.
		 * The circle can also be drawn filled with the color by specifying true for the \a filled parameter.
		 * @param x is the X coordinate of the center of the circle in pixels
		 * @param y is the Y coordinate of the center of the circle in pixels.
		 * @param radius is the radius of the circle in pixels.
		 * @param color is the color to draw the circle with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 * @param filled specifies if the circle should be filled with color or drawn as a wireframe. Can be true or false. Default value is false.
		 */
		void Circle(int x, int y, int radius, int color, bool filled = false);
		
		/**
		 * Draws an arc on the image in the specified color, from the \a startAngle to the \a endAngle with a radius of \a radius.
		 * The \a endAngle should always be greater than the \a startAngle.
		 * @param x is the X coordinate of the center of the arc in pixels.
		 * @param y is the Y coordinate of the center of the arc in pixels.
		 * @param radius is the radius of the arc in pixels.
		 * @param startAngle is the angle in degrees to begin drawing the arc from the image to. This can be an integer value of 0 to 359.
		 * @param endAngle is the angle in degrees at which to stop drawing the arc. This can be an integer value of 0 to 359.
		 * @param color is the color to draw the arc with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		void Arc(int x, int y, int radius, int startAngle, int endAngle, int color);
		
		/**
		 * Draws a triangle on the image.\n
		 * You specify where the triangle is to be drawn by using 3 pairs of point coordinates.\n
		 * The triangle can also be drawn filled with the color by specifying true for the \a filled parameter.
		 * @param x1 is the X coordinate in pixels for the first point.
		 * @param y1 is the Y coordinate in pixels for the first point.
		 * @param x2 is the X coordinate in pixels for the second point.
		 * @param y2 is the Y coordinate in pixels for the second point.
		 * @param x3 is the X coordinate in pixels for the third point.
		 * @param y3 is the Y coordinate in pixels for the third point.
		 * @param color is the color to draw the ellipse with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 * @param filled specifies if the ellipse should be filled with color or drawn as a wireframe. Can be true or false. Default value is false.
		 */
		void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, bool filled = false);
		
		/**
		 * Fills an enclosed area that the point (x, y) lies within with the specified color.\n
		 * An area is considered enclosed if there are pixels of the color \a color surrounding the point (x, y).
		 * @param x is the X coordinate in pixels for the point
		 * @param y is the Y coordinate in pixels for the point
		 * @param color is the color to fill the area with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		void Fill(int x, int y, int color);
		
		// utility
		
		/**
		 * Fills the entire image with the specified color. Calling without any parameters will fill with BLACK.
		 * @param color is the color to fill the image with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		void Clear(int color = 0);
		
		/**
		 * Saves the image to a windows BMP file.
		 * @param fileName is the name of the file to save the image to.
		 */
		void Save(const char* fileName);
		
		// member accessor
		
		/**
		 * \return a pointer to the Allegro BITMAP; ImageResource::allegroBitmap_ or 0 if the image is invalid.
		 */
		BITMAP* GetBitmap();
		
		/**
		 * \return the width of the image in pixels
		 */
		int GetWidth();
		
		/**
		 * \return the height of the image in pixels
		 */
		int GetHeight();
		
	private:
	
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * hidden copy constructor
		 */
		ImageResource(const ImageResource& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const ImageResource& operator=(const ImageResource& rhs);
		
		/**
		 * Loads an image using the Allegro load_bitmap function.
		 * Can load from BMP, PCX, TGA.
		 * \return a pointer to an Allegro BITMAP containing the loaded image data.
		 */
		BITMAP* LoadBitmapInternal(const char* fileName);
		
		/**
		 * Loads an image using a custom PNG loader.
		 * Can load from PNG.
		 * \return a pointer to an Allegro BITMAP containing the loaded image data.
		 */
		BITMAP* LoadPNGInternal(const char* fileName);
		
		/**
		 * \var allegroBitmap_
		 * \brief An Allegro BITMAP to hold the image data.
		 *
		 * Below is the BITMAP structure straight from the Allegro documentation
		 * \code
typedef struct BITMAPtag
{
	int w, h;               - size of the bitmap in pixels
	int clip;               - non-zero if clipping is turned on
	int cl, cr, ct, cb;     - clipping rectangle left, right, top, and bottom
	unsigned char *line[];  - pointers to the start of each row of pixel data
} BITMAP;
		 * \endcode
		 * All the values of this structure should be regarded as read-only, with the exception of the line field.
		 */
		BITMAP* allegroBitmap_;
	}; // end class

} // end namespace
#endif


