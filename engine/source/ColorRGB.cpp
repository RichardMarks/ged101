
// CODESTYLE: v2.0

// ColorRGB.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class for creating 24-bit colors from red, green, and blue values.

/**
 * \file ColorRGB.cpp
 * \brief 24-bit Color Type - Implementation
 */


// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "ColorRGB.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	
	/**************************************************************************/
	
	ColorRGB::ColorRGB() :
		red_(0),
		green_(0),
		blue_(0)
	{
	}
	
	/**************************************************************************/
	
	ColorRGB::ColorRGB(int red, int green, int blue) :
		red_(red),
		green_(green),
		blue_(blue)
	{
	}
	
	/**************************************************************************/
	
	ColorRGB::ColorRGB(const char* htmlColor)
	{
		if (strlen(htmlColor) < 7)
		{
			LogError("%s is an invalid HTML Color.\nExpected format of #RRGGBB where R,G,B are HEX values from 00 to FF", htmlColor);
			red_ = 0;
			green_ = 0;
			blue_ = 0;
		}
		else
		{
			char red[5]; 	sprintf(red, "0x%c%c", htmlColor[1], htmlColor[2]); 	red_ 	= atoi(red);
			char green[5]; 	sprintf(green, "0x%c%c", htmlColor[3], htmlColor[4]); 	green_ 	= atoi(green);
			char blue[5]; 	sprintf(blue, "0x%c%c", htmlColor[5], htmlColor[6]); 	blue_ 	= atoi(blue);
		}
	}
	
	/**************************************************************************/
	
	ColorRGB::~ColorRGB()
	{
		red_ 	= 0;
		green_ 	= 0;
		blue_ 	= 0;
	}
	
	/**************************************************************************/
	
	void ColorRGB::Set(int red, int green, int blue)
	{
		red_ 	= red;
		green_ 	= green;
		blue_ 	= blue;
	}
	
	/**************************************************************************/
	
	void ColorRGB::SetRed(int red)
	{
		red_ = red;
	}
	
	/**************************************************************************/
	
	void ColorRGB::SetGreen(int green)
	{
		green_ = green;
	}
	
	/**************************************************************************/
	
	void ColorRGB::SetBlue(int blue)
	{
		blue_ = blue;
	}
	
	/**************************************************************************/
	
	int ColorRGB::Get()
	{
		return makecol(red_, green_, blue_);
	}
	
	/**************************************************************************/
	
	int ColorRGB::GetRed()
	{
		return red_;
	}
	
	/**************************************************************************/
	
	int ColorRGB::GetGreen()
	{
		return green_;
	}
	
	/**************************************************************************/
	
	int ColorRGB::GetBlue()
	{
		return blue_;
	}
	
} // end namespace


