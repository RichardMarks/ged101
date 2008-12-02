
// CODESTYLE: v2.0

// Tileset.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage a list of pointers to the ImageResource class by name

/**
 * \file Tileset.cpp
 * \brief Tile-Based Module - Implementation
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// include the complementing header
#include "Tileset.h"

// include the image resource header
#include "ImageResource.h"

// include the image list header
#include "ImageList.h"

// include the name directory header
#include "NameDirectory.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	Tileset::Tileset()
	{
		names_ = new NameDirectory();
		images_ = new ImageList();
	}
	
	/**************************************************************************/
	
	Tileset::~Tileset()
	{
		Destroy();
	}
	
	/**************************************************************************/
		
	void Tileset::Add(const char* tileName, ImageResource* image)
	{
		images_->Add(image);
		
		unsigned int count = static_cast<unsigned int>(images_->GetCount() - 1);
		names_->Add(tileName, count);
	}
	
	/**************************************************************************/
	
	void Tileset::AddRange(const char* tileNamePrefix, unsigned int count, ...)
	{
		va_list va;
		va_start(va, count);
		
		for (unsigned int index = 0; index < count; index++)
		{
			// add the image
			ImageResource* image = va_arg(va, ImageResource*);
			images_->Add(image);
			
			// create a new tilename 
			char tileName[1024];
			snprintf(tileName, 1024, "%s%d", tileNamePrefix, index);
			
			// add the name
			unsigned int count = static_cast<unsigned int>(images_->GetCount() - 1);
			names_->Add(tileName, count);
		}
		va_end(va);
	}
	
	/**************************************************************************/
	
	ImageResource* Tileset::Get(const char* tileName)
	{
		return images_->Get(names_->Get(tileName));
	}
	
	/**************************************************************************/
	
	ImageResource* Tileset::Get(unsigned int tileID)
	{
		return images_->Get(tileID);
	}
	
	/**************************************************************************/
	
	unsigned int Tileset::GetIndex(const char* tileName)
	{
		return names_->Get(tileName);
	}
	
	/**************************************************************************/
	
	unsigned int Tileset::GetCount()
	{
		return images_->GetCount();
	}
	
	/**************************************************************************/

	void Tileset::Destroy()
	{
		if (0 != names_)
		{
			delete names_;
			names_ = 0;
		}
		
		if (0 != images_)
		{
			delete images_;
			images_ = 0;
		}
	}

} // end namespace


