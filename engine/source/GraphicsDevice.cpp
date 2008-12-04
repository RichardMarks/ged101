
// CODESTYLE: v2.0

// GraphicsDevice.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Interface to the physical graphics device; The screen.

/**
 * \file GraphicsDevice.cpp
 * \brief Graphics Device Interface - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "GraphicsDevice.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"


namespace ENGINE
{
	GraphicsDeviceSingleton* GraphicsDeviceSingleton::GetInstance()
	{
		// return the singleton instance
		static GraphicsDeviceSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	void GraphicsDeviceSingleton::BeginScene(int color)
	{
		if ((0 == primaryDisplayBuffer_) || (0 == secondaryDisplayBuffer_))
		{
			LogFatal("Attempted to call BeginScene on an invalid Graphics Device!");
			return;
		}
		
		secondaryDisplayBuffer_->Clear(color);
	}
	
	/**************************************************************************/
	
	void GraphicsDeviceSingleton::EndScene()
	{
		if ((0 == primaryDisplayBuffer_) || (0 == secondaryDisplayBuffer_))
		{
			LogFatal("Attempted to call EndScene on an invalid Graphics Device!");
			return;
		}
		
		secondaryDisplayBuffer_->Blit(primaryDisplayBuffer_, 0, 0, 0, 0, displayWidth_, displayHeight_);
	}
	
	/**************************************************************************/
	
	bool GraphicsDeviceSingleton::SetDisplayMode(GraphicsDeviceDisplayMode mode)
	{
		displayMode_ = mode;
		
		int gfx = GFX_TEXT;
		
		if (GraphicsDevice_Windowed == displayMode_)
		{
			gfx = GFX_AUTODETECT_WINDOWED;
		}
		else if (GraphicsDevice_Fullscreen == displayMode_)
		{
			gfx = GFX_AUTODETECT_FULLSCREEN;
		}
		
		// try to set the given mode
		int result = 0;
		
		result = set_gfx_mode(gfx, displayWidth_, displayHeight_, 0, 0);
		
		if (0 == result)
		{
			// we are good
			
			// make sure we release the previous buffers
			Destroy();
			
			// create the buffers
			primaryDisplayBuffer_ = new ImageResource(screen);
			
			secondaryDisplayBuffer_ = new ImageResource(displayWidth_, displayHeight_);
			
			return true;
		}
		else if (result < 0)
		{
			LogFatal("Could not set the display mode to %dx%d %s resolution @ %dbits per pixel!", 
				displayWidth_, 
				displayHeight_,
				(GraphicsDevice_Windowed == displayMode_) ? "windowed" : "fullscreen",
				static_cast<int>(displayBitsPerPixel_)); 		
		}
		
		return false;
	}
	
	/**************************************************************************/
	
	void GraphicsDeviceSingleton::SetDisplayResolution(int displayWidth, int displayHeight)
	{
		displayWidth_ = displayWidth;
		displayHeight_ = displayHeight_;
	}
	
	/**************************************************************************/
	
	void GraphicsDeviceSingleton::SetDisplayColorDepth(GraphicsDeviceDisplayDepth bitsPerPixel)
	{
		// set the class bpp to the passed bpp
		displayBitsPerPixel_ = bitsPerPixel;
		
		// actually set the bpp
		int bpp = 8;
		switch(displayBitsPerPixel_)
		{
			case GraphicsDevice_8bit:  { } break;
			case GraphicsDevice_15bit: { bpp = 15; } break;
			case GraphicsDevice_16bit: { bpp = 16; } break;
			case GraphicsDevice_24bit: { bpp = 24; } break;
			case GraphicsDevice_32bit: { bpp = 32; } break;
		}
		set_color_depth(bpp);
	}
	
	/**************************************************************************/
	
	bool GraphicsDeviceSingleton::SetDisplay(
			int displayWidth, 
			int displayHeight, 
			GraphicsDeviceDisplayDepth bitsPerPixel, 
			GraphicsDeviceDisplayMode mode)
	{
		SetDisplayColorDepth(bitsPerPixel);
		SetDisplayResolution(displayWidth, displayHeight);
		return SetDisplayMode(mode);
	}
	
	/**************************************************************************/
	
	GraphicsDeviceDisplayMode GraphicsDeviceSingleton::GetDisplayMode()
	{
		return displayMode_;
	}
	
	/**************************************************************************/
	
	int GraphicsDeviceSingleton::GetDisplayWidth()
	{
		return displayWidth_;
	}
	
	/**************************************************************************/
	
	int GraphicsDeviceSingleton::GetDisplayHeight()
	{
		return displayHeight_;
	}
	
	/**************************************************************************/
	
	GraphicsDeviceDisplayDepth GraphicsDeviceSingleton::GetDisplayBitsPerPixel()
	{
		return displayBitsPerPixel_;
	}
	
	/**************************************************************************/
	
	ImageResource* GraphicsDeviceSingleton::GetPrimaryDisplayBuffer()
	{
		return primaryDisplayBuffer_;
	}
	
	/**************************************************************************/
	
	ImageResource* GraphicsDeviceSingleton::GetSecondaryDisplayBuffer()
	{
		return secondaryDisplayBuffer_;
	}
	
	/**************************************************************************/
	
	void GraphicsDeviceSingleton::Destroy()
	{
		if (0 != primaryDisplayBuffer_)
		{
			delete primaryDisplayBuffer_;
			primaryDisplayBuffer_ = 0;
		}
		
		if (0 != secondaryDisplayBuffer_)
		{
			delete secondaryDisplayBuffer_;
			secondaryDisplayBuffer_ = 0;
		}
	}
	
	/**************************************************************************/
	
	GraphicsDeviceSingleton::GraphicsDeviceSingleton() :
		primaryDisplayBuffer_(0),
		secondaryDisplayBuffer_(0),
		displayMode_(GraphicsDevice_Windowed),
		displayWidth_(GRAPHICS_DEVICE_FALLBACK_DISPLAY_WIDTH),
		displayHeight_(GRAPHICS_DEVICE_FALLBACK_DISPLAY_HEIGHT),
		displayBitsPerPixel_(GRAPHICS_DEVICE_FALLBACK_DISPLAY_BPP)
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	GraphicsDeviceSingleton::~GraphicsDeviceSingleton()
	{
		// implement class destructor here
		Destroy();
	} // end destructor

} // end namespace


