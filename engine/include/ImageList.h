
// CODESTYLE: v2.0

// ImageList.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a list of pointers to the ImageResource class

/**
 * \file ImageList.h
 * \brief Graphics Module - Header
 */

#ifndef __IMAGELIST_H__
#define __IMAGELIST_H__

#include <vector>
#include <cstdarg>

namespace ENGINE
{
	// forward declare the classes we need
	class ImageResource;
	
	/**
	 * \namespace ENGINE::IMGLST
	 * \brief contains the ImageList specific enumerations
	 */
	namespace IMGLST
	{
		/**
		 * \enum AddImageArgType
		 * \brief specify the variable arguments' type
		 */
		enum AddImageArgType
		{
			//! the argument is assumed to be a pointer to an ImageResource
			ArgIsPointer,
			//! the argument is assumed to be a C-string specifying a filename
			ArgIsFilename
		};
	} // end of namespace
	
	/**
	 * \class ImageList
	 * \brief A class to hold a list of pointers to the ImageResource class
	 */
	class ImageList
	{
	public:
		/**
		 * default constructor
		 */
		ImageList();
		
		/**
		 * alternate constructor lets you add multiple images to the list either by filename or pointer
		 * @param count is the number of arguments passed
		 * @param argType is the type of arguments you intend to use. Either IMGLST::ArgIsPointer or IMGLST::ArgIsFilename
		 * @param ... is the variable argument list
		 */
		ImageList(unsigned int count, IMGLST::AddImageArgType argType, ...);

		/**
		 * De-allocate any allocated memory by calling ImageList::Destroy()
		 */
		~ImageList();
		
		/**
		 * Add an image to the list by pointer
		 * @param image is a pointer to an allocated instance of the ImageResource class
		 */
		void Add(ImageResource* image);
		
		/**
		 * Add an image to the list by filename
		 * @param fileName is the name of the file that holds the image data to load
		 */
		bool Add(const char* fileName);
		
		/**
		 * Gets an image from the list
		 * @param index is the ID for the image to get
		 * \return a pointer to the image, or 0 if the index is out of range, or if the stored image is invalid
		 */
		ImageResource* Get(unsigned int index);
		
#if 0
		/**
		 * Gets an image from the list using array-notation
		 * @param index is the ID for the image to get
		 * \return a pointer to the image, or 0 if the index is out of range, or if the stored image is invalid
		 */
		ImageResource* operator[](unsigned int index);
#endif
	
		/**
		 * De-allocate any allocated memory by calling ImageList::Destroy() to clear out the list
		 */
		void Clear();
		
		/**
		 * Gets the number of images
		 * \return the number of images that are in the list
		 */
		unsigned int GetCount();
		
	private:
		
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * hidden copy constructor
		 */
		ImageList(const ImageList& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const ImageList& operator=(const ImageList& rhs);
		
		/**
		 * \var images_
		 * \brief an STL vector of pointers to the ImageResource class
		 */
		std::vector<ImageResource*> images_;
		
	}; // end class

} // end namespace
#endif


