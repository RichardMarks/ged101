
// CODESTYLE: v2.0

// GraphicsDevice.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Interface to the physical graphics device; The screen.

/**
 * \file GraphicsDevice.cpp
 * \brief Graphics Device Interface - Implementation
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
	
	void GraphicsDeviceSingleton::BeginScene(int color = 0)
	{
	}
	
	/**************************************************************************/
	
	void GraphicsDeviceSingleton::EndScene()
	{
	}
	
	/**************************************************************************/
	
	bool GraphicsDeviceSingleton::SetDisplayMode(GraphicsDeviceDisplayMode mode)
	{
		displayMode_ = mode;
	}
	
	/**************************************************************************/
	
	bool GraphicsDeviceSingleton::SetDisplayResolution(int displayWidth, int displayHeight)
	{
	}
	
	/**************************************************************************/
	
	bool GraphicsDeviceSingleton::SetDisplayColorDepth(GraphicsDeviceDisplayDepth bitsPerPixel)
	{
	}
	
	/**************************************************************************/
	
	bool GraphicsDeviceSingleton::SetDisplay(
			int displayWidth, 
			int displayHeight, 
			GraphicsDeviceDisplayDepth bitsPerPixel, 
			GraphicsDeviceDisplayMode mode)
	{
	}
	
	/**************************************************************************/
	
	GraphicsDeviceDisplayMode GraphicsDeviceSingleton::GetDisplayMode()
	{
	}
	
	/**************************************************************************/
	
	int GraphicsDeviceSingleton::GetDisplayWidth()
	{
	}
	
	/**************************************************************************/
	
	int GraphicsDeviceSingleton::GetDisplayHeight()
	{
	}
	
	/**************************************************************************/
	
	GraphicsDeviceDisplayDepth GraphicsDeviceSingleton::GetDisplayBitsPerPixel()
	{
	}
	
	/**************************************************************************/
	
	ImageResource* GraphicsDeviceSingleton::GetPrimaryDisplayBuffer()
	{
	}
	
	/**************************************************************************/
	
	ImageResource* GraphicsDeviceSingleton::GetSecondaryDisplayBuffer()
	{
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


