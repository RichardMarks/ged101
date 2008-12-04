
// CODESTYLE: v2.0

// NameDirectory.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage a directory of names for using simple name/index lookup tables

/**
 * \file NameDirectory.cpp
 * \brief Generic Utility System Module - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// include the complementing header
#include "NameDirectory.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	NameDirectory::NameDirectory()
	{
	}
	
	/**************************************************************************/
	
	NameDirectory::~NameDirectory()
	{
		Destroy();
	}
	
	/**************************************************************************/
	
	void NameDirectory::Add(const char* name, unsigned int value)
	{
		lut_[name] = value;
	}
	
	/**************************************************************************/
	
	unsigned int NameDirectory::Get(const char* name)
	{
		return static_cast<unsigned int>(lut_[name]);
	}
	
	/**************************************************************************/
	
	void NameDirectory::Destroy()
	{
		lut_.clear();
	}
	
} // end namespace


