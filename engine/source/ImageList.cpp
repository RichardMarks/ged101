
// CODESTYLE: v2.0

// ImageList.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a list of pointers to the ImageResource class

/**
 * \file ImageList.cpp
 * \brief Graphics Module - Implementation
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// include the complementing header
#include "ImageList.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	ImageList::ImageList()
	{
	}
	
	/**************************************************************************/
	
	ImageList::ImageList(unsigned int count, IMGLST::AddImageArgType argType, ...)
	{
		va_list va;
		va_start(va, argType);

		if (IMGLST::ArgIsPointer == argType)
		{
			for (unsigned int index = 0; index < count; index++)
			{
				ImageResource* image = va_arg(va, ImageResource*);
				images_.push_back(image);
			}
		}
		else if (IMGLST::ArgIsFilename == argType)
		{
			for (unsigned int index = 0; index < count; index++)
			{
				const char* fileName = strdup(va_arg(va, const char*));
				ImageResource* image = new ImageResource();
				if (image->Load(fileName))
				{
					images_.push_back(image);
				}
				else
				{
					LogError("could not load image from %s into list index %d!", fileName, index);
				}
			}
		}

		va_end(va);
	}
	
	/**************************************************************************/
	
	ImageList::~ImageList()
	{
		Destroy();
	}
	
	/**************************************************************************/
	
	void ImageList::Add(ImageResource* image)
	{
		images_.push_back(image);
	}
	
	/**************************************************************************/
	
	bool ImageList::Add(const char* fileName)
	{
		ImageResource* image = new ImageResource();
		if (image->Load(fileName))
		{
			images_.push_back(image);
			return true;
		}
		else
		{
			LogError("could not load image from %s into list index %d!", fileName, images_.size());
		}
		return false;
	}
	
	/**************************************************************************/
	
	ImageResource* ImageList::Get(unsigned int index)
	{
		return (index < images_.size()) ? images_.at(index) : 0;
	}
	
	/**************************************************************************/
	
	ImageResource* ImageList::operator[](unsigned int index)
	{
		return (index < images_.size()) ? images_.at(index) : 0;
	}
	
	/**************************************************************************/
	
	void ImageList::Clear()
	{
		Destroy();
	}
	
	/**************************************************************************/
	
	void ImageList::Destroy()
	{
		// delete all images
		unsigned int index = 0;
		for (index = 0; index < images_.size(); index++)
		{
			if (0 != images_[index])
			{
				delete images_[index];
				images_[index] = 0;
			}
		}
		images_.clear();
	}
	
} // end namespace


