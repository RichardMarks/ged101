
// CODESTYLE: v2.0

// BitmapFont.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: holds the data for a bitmapped font

/**
 * \file BitmapFont.cpp
 * \brief Bitmapped-font printing system - Implementation
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "BitmapFont.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	BitmapFont::BitmapFont() :
		letterWidth_(8),
		letterHeight_(8),
		spacing_(2),
		fontImage_(0)
	{
		// default font
		const int defaultFont[] =
		{
			0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,
			0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,1,1,1,0,0,
			1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,
			1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,
			0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,
			0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,
			0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,
			0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
			0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
			0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
			1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,
			1,0,1,0,0,1,0,1,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,1,1,0,
			0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,
			1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,
			1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,
			1,0,1,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,
			1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
			1,0,0,1,1,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,0,1,1,0,0,
			0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,
			0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
			1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,
			1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,
			0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
			1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,
			1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
			1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,
			1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
			1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,
			1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,0,1,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,
			0,1,1,1,1,0,0,0,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,
			0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
			1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,
			1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,
			0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,
			1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,
			0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,
			0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,
			0,0,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,
			0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,
			0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,
			0,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,
			1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,
			0,0,1,1,1,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,1,
			0,1,1,1,1,1,0,0,1,1,0,1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,
			0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,
			1,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,
			0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,
			0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
			0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
			0,0,1,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,
			0,0,0,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,
			0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
			0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
			0,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,
			0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,
			0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
			1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,
			0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,
			1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,
			0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,
			1,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,
			0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,1,1,0,
			0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,
			0,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,
			0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
			0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,
			0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,
			0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,
			0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,0,0,
			1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,
			0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,
			0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,
			0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,
			0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,0,0,1,0,
			0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,1,1,0,1,1,0,0,0,1,1,0,
			0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,0,0,1,0,0,1,1,1,0,0,
			0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
			1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,0,1,1,0,
			1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,0,0,1,0,
			0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,
			0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,
			0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,
			1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,
			1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,
			0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,
			1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,
			0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,0,
			1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,
			0,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,
			0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,
			0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,
			0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,
			1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,
			1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,
			0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
			1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,
			0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,
			1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,0,0,
			1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,1,1,1,1,0,0,
			0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,
			1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,
			0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
			0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,
			0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,
			0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,0,0,0,0,
			0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,
			1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,
			0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,0,1,1,0,0,
			1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,
			0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,0,0,1,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,
			1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,
			0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,
			0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
			0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
			0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,
			0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
			1,1,0,0,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,
			0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
			0,0,1,1,1,0,0,0,0,1,1,0,0,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,0,
			0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,0,
			0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
			0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,0,
			0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
			0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,
			0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
			1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
			0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,
			0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,
			0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,
			0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,
			0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,0,
			0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,0,
			0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,
			0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,0,
			0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,
			1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
			0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,
			0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,
			0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,1,1,1,1,0,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,
			0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,
			0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,
			1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
			0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
			0,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
			0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,
			0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
			0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
			1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,
			1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,
			1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
			1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 
		};
		int whitePixel = makecol(255, 255, 255);
		fontImage_ = new ImageResource(128, 128, makecol(255, 0, 255));
		for (int y = 0; y < 128; y++)
		{
			for (int x = 0; x < 128; x++)
			{
				if (0 != defaultFont[x + (y * 128)])
				{
					fontImage_->SetPixel(x, y, whitePixel);
				}
			}
		}
	} // end constructor
	
	/**************************************************************************/
	
	BitmapFont::~BitmapFont()
	{
		// implement class destructor here
		Destroy();
	} // end destructor

	/**************************************************************************/
	
	bool BitmapFont::Load(const char* filePath, int letterWidth, int letterHeight, int spacing)
	{
		Destroy();
		
		fontImage_ = new ImageResource();
		
		if (!fontImage_->Load(filePath))
		{
			LogError("Could not load font resource from %s!", filePath);
			return false;
		}
		
		letterWidth_ = letterWidth;
		letterHeight_ = letterHeight;
		spacing_ = spacing;
		return true;
	}
	
	/**************************************************************************/
	
	void BitmapFont::Create(ImageResource* source, int letterWidth, int letterHeight, int spacing)
	{
		Destroy();
		
		fontImage_ = new ImageResource();
		
		fontImage_->Create(source->GetBitmap());
		
		letterWidth_ = letterWidth;
		letterHeight_ = letterHeight;
		spacing_ = spacing;
	}
	
	/**************************************************************************/
	
	void BitmapFont::Print(ImageResource* destination, int x, int y, const char* text, ...)
	{
		char textBuffer[BITFNT_MAX_STRING_LENGTH];
		va_list va;
		va_start(va, text);
		vsnprintf(textBuffer, BITFNT_MAX_STRING_LENGTH - 1, text, va);
		va_end(va);
		
		unsigned int textLength = strlen(textBuffer);
		
		// save the origin, and a drawing cursor location
		int originX = x;
		int originY = y;
		int cursorX = x;
		int cursorY = y;
		
		// default tab size is 8
		int tabSize = (8 * letterWidth_) + (7 * spacing_);
		
		int fontImageWidth = fontImage_->GetWidth();
		int fontImageHeight = fontImage_->GetHeight();
		
		for (unsigned int index = 0; index < textLength; index++)
		{
			switch(textBuffer[index])
			{
				case '\n':
				{
					// handle the new line
					cursorX = originX;
					cursorY += letterHeight_;
					cursorY += spacing_;
				} break;
				
				case '\t':
				{
					// handle the tab
					cursorX += tabSize;
				} break;
				
				default:
				{
					// any other character just gets printed
					
					// get the letter
					int letter = textBuffer[index];
					
					// find the position of the letter
					int letterX = (letter / fontImageWidth) * letterWidth_;
					int letterY = (letter % fontImageHeight) * letterHeight_;
					
					// blit the damn thing!
					fontImage_->Blit(destination, letterX, letterY, cursorX, cursorY, letterWidth_, letterHeight_);
					
					// advance cursor position
					cursorX += letterWidth_;
					cursorX += spacing_;
				} break;
			}
		}
	}
	
	/**************************************************************************/
	
	int BitmapFont::GetLetterWidth()
	{
		return letterWidth_;
	}
	
	/**************************************************************************/
	
	int BitmapFont::GetLetterHeight()
	{
		return letterHeight_;
	}
	
	/**************************************************************************/
	
	int BitmapFont::GetLetterSpacing()
	{
		return spacing_;
	}
	
	/**************************************************************************/
	
	ImageResource* BitmapFont::GetFontImage()
	{
		return fontImage_;
	}
	
	/**************************************************************************/
	
	void BitmapFont::Destroy()
	{
		if (0 != fontImage_)
		{
			delete fontImage_;
		}
	}
	
} // end namespace


