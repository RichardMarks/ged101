
// CODESTYLE: v2.0

// HorizontalScrollingLayer.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A layer that can scroll an image in any direction at any speed

/**
 * \file ScrollingLayer.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include the complementing header
#include "HorizontalScrollingLayer.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	HorizontalScrollingLayer::HorizontalScrollingLayer() :
		translucency_(1.0f),
		layerWidth_(0),
		layerHeight_(0)
	{
	}
	
	/**************************************************************************/
	
	HorizontalScrollingLayer::HorizontalScrollingLayer(ImageResource* image, float scrollSpeed, float translucency, float x, float y)
	{
		SetPosition(x, y);
		SetScrollSpeed(scrollSpeed);
		SetTranslucency(translucency);
		SetImage(image);
	}
	
	/**************************************************************************/
	
	HorizontalScrollingLayer::HorizontalScrollingLayer(const char* imageFileName, float scrollSpeed, float translucency, float x, float y)
	{
		SetPosition(x, y);
		SetScrollSpeed(scrollSpeed);
		SetTranslucency(translucency);
		SetImage(imageFileName);
	}
	
	/**************************************************************************/
		
	HorizontalScrollingLayer::~HorizontalScrollingLayer()
	{
		Destroy();
	}
	
	/**************************************************************************/

	bool HorizontalScrollingLayer::Initialize()
	{
		return true;
	}
	
	/**************************************************************************/
	
	void HorizontalScrollingLayer::Update(float deltaTime)
	{
		if (layerScrollSpeed_ == 0.0f)
		{
			// we don't update the layer's position since the layer does not move there is no point.
			return;
		}
		
		layerPosition_[0] += layerScrollSpeed_ * deltaTime;
		int x = static_cast<int>(layerPosition_[0]);
		if (layerScrollSpeed_ > 0.0f)
		{
			// layer is moving to the right
			if (x > layerWidth_)
			{
				layerPosition_[0] = static_cast<float>(0);
			}
		}
		else
		{
			// layer is moving to the left
			if (x < 0)
			{
				layerPosition_[0] = static_cast<float>(layerWidth_);
			}
		}
	}
	
	/**************************************************************************/

	void HorizontalScrollingLayer::Render(ImageResource* target)
	{
		int x = static_cast<int>(layerPosition_[0]);
		int y = static_cast<int>(layerPosition_[1]);
		
		// are we drawing this thing with translucency
		if (translucency_ < 1.0f)
		{
			drawingSurface_->BlitAlpha(target, x - layerWidth_, y, translucency_);
			drawingSurface_->BlitAlpha(target, x, y, translucency_);
			drawingSurface_->BlitAlpha(target, x + layerWidth_, y, translucency_);
			return;
		}
		
		// or are we drawing this thing opaque
		int w = drawingSurface_->GetWidth();
		int h = drawingSurface_->GetHeight();
		
		drawingSurface_->BlitMasked(target, 0, 0, x - layerWidth_, y, w, h);
		drawingSurface_->BlitMasked(target, 0, 0, x, y, w, h);
		drawingSurface_->BlitMasked(target, 0, 0, x + layerWidth_, y, w, h);
	}

	/**************************************************************************/
	
	void HorizontalScrollingLayer::Destroy()
	{
	}
	
	/**************************************************************************/
	
	void HorizontalScrollingLayer::SetImage(ImageResource* image)
	{
		Destroy();
		
		if (0 == image)
		{
			LogWarning("setting layer image to an invalid image resource!");
		}
		
		drawingSurface_ = image;
		
		layerWidth_ = drawingSurface_->GetWidth();
		layerHeight_ = drawingSurface_->GetHeight();
	}
	
	/**************************************************************************/
	
	void HorizontalScrollingLayer::SetImage(const char* imageFileName)
	{
		Destroy();
		
		drawingSurface_ = new ImageResource(imageFileName);
		
		if (0 == drawingSurface_)
		{
			LogWarning("layer image is invalid!");
		}
		
		layerWidth_ = drawingSurface_->GetWidth();
		layerHeight_ = drawingSurface_->GetHeight();
	}
	
	/**************************************************************************/
	
	void HorizontalScrollingLayer::SetScrollSpeed(float scrollSpeed)
	{
		layerScrollSpeed_ = scrollSpeed;
	}
	
	/**************************************************************************/
	
	void HorizontalScrollingLayer::SetTranslucency(float translucency)
	{
		translucency_ = translucency;
	}
	
	/**************************************************************************/
	
	void HorizontalScrollingLayer::SetPosition(float x, float y)
	{
		layerPosition_[0] = x;
		layerPosition_[1] = y;
	}
	
	/**************************************************************************/
		
	ImageResource* HorizontalScrollingLayer::GetImage()
	{
		return drawingSurface_;
	}
	
	/**************************************************************************/
	
	float HorizontalScrollingLayer::GetScrollSpeed()
	{
		return layerScrollSpeed_;
	}
	
	/**************************************************************************/
	
	float HorizontalScrollingLayer::GetTranslucency()
	{
		return translucency_;
	}
	
	/**************************************************************************/
	
	int HorizontalScrollingLayer::GetWidth()
	{
		return layerWidth_;
	}
	
	/**************************************************************************/
	
	int HorizontalScrollingLayer::GetHeight()
	{
		return layerHeight_;
	}
	
} // end namespace


