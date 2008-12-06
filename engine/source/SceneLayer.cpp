
// CODESTYLE: v2.0

// SceneLayer.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: The base class that all Scene Layer types inherit from

/**
 * \file SceneLayer.cpp
 * \brief Scene Management Module - Implementation
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the complementing header
#include "SceneLayer.h"

// include the image resource header
#include "ImageResource.h"

namespace ENGINE
{
	SceneLayer::SceneLayer() :
		drawingSurface_(0)
	{
	}
	
	/**************************************************************************/
	
	SceneLayer::~SceneLayer()
	{
		if (0 != drawingSurface_)
		{
			delete drawingSurface_;
			drawingSurface_ = 0;
		}
	}
	
} // end namespace


