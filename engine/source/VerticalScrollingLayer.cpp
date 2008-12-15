
// CODESTYLE: v2.0

// VerticalScrollingLayer.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A layer that holds a single image, and can scroll either up or down

/**
 * \file VerticalScrollingLayer.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include the complementing header
#include "VerticalScrollingLayer.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	VerticalScrollingLayer::VerticalScrollingLayer() :
		translucency_(1.0f),
		layerWidth_(0),
		layerHeight_(0)
	{
	}
	
	/**************************************************************************/
	
	VerticalScrollingLayer::VerticalScrollingLayer(ImageResource* image, float scrollSpeed, float translucency, float x, float y)
	{
		SetPosition(x, y);
		SetScrollSpeed(scrollSpeed);
		SetTranslucency(translucency);
		SetImage(image);
	}
	
	/**************************************************************************/
	
	VerticalScrollingLayer::VerticalScrollingLayer(const char* imageFileName, float scrollSpeed, float translucency, float x, float y)
	{
		SetPosition(x, y);
		SetScrollSpeed(scrollSpeed);
		SetTranslucency(translucency);
		SetImage(imageFileName);
	}
	
	/**************************************************************************/
		
	VerticalScrollingLayer::~VerticalScrollingLayer()
	{
		Destroy();
	}
	
	/**************************************************************************/

	bool VerticalScrollingLayer::Initialize()
	{
		return true;
	}
	
	/**************************************************************************/
	
	void VerticalScrollingLayer::Update(float deltaTime)
	{
		if (layerScrollSpeed_ == 0.0f)
		{
			// we don't update the layer's position since the layer does not move there is no point.
			return;
		}
		
		layerPosition_[1] += layerScrollSpeed_ * deltaTime;
		int y = static_cast<int>(layerPosition_[1]);
		if (layerScrollSpeed_ > 0.0f)
		{
			// layer is moving down
			if (y > layerWidth_)
			{
				layerPosition_[1] = static_cast<float>(0);
			}
		}
		else
		{
			// layer is moving up
			if (y < 0)
			{
				layerPosition_[1] = static_cast<float>(layerHeight_);
			}
		}
	}
	
	/**************************************************************************/

	void VerticalScrollingLayer::Render(ImageResource* target)
	{
		int x = static_cast<int>(layerPosition_[0]);
		int y = static_cast<int>(layerPosition_[1]);
		
		// are we drawing this thing with translucency
		if (translucency_ < 1.0f)
		{
			drawingSurface_->BlitAlpha(target, x, y - layerHeight_, translucency_);
			drawingSurface_->BlitAlpha(target, x, y, translucency_);
			drawingSurface_->BlitAlpha(target, x, y + layerHeight_, translucency_);
			return;
		}
		
		// or are we drawing this thing opaque
		int w = drawingSurface_->GetWidth();
		int h = drawingSurface_->GetHeight();
		
		drawingSurface_->BlitMasked(target, 0, 0, x, y - layerHeight_, w, h);
		drawingSurface_->BlitMasked(target, 0, 0, x, y, w, h);
		drawingSurface_->BlitMasked(target, 0, 0, x, y + layerHeight_, w, h);
	}

	/**************************************************************************/
	
	void VerticalScrollingLayer::Destroy()
	{
	}
	
	/**************************************************************************/
	
	void VerticalScrollingLayer::SetImage(ImageResource* image)
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
	
	void VerticalScrollingLayer::SetImage(const char* imageFileName)
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
	
	void VerticalScrollingLayer::SetScrollSpeed(float scrollSpeed)
	{
		layerScrollSpeed_ = scrollSpeed;
	}
	
	/**************************************************************************/
	
	void VerticalScrollingLayer::SetTranslucency(float translucency)
	{
		translucency_ = translucency;
	}
	
	/**************************************************************************/
	
	void VerticalScrollingLayer::SetPosition(float x, float y)
	{
		layerPosition_[0] = x;
		layerPosition_[1] = y;
	}
	
	/**************************************************************************/
		
	ImageResource* VerticalScrollingLayer::GetImage()
	{
		return drawingSurface_;
	}
	
	/**************************************************************************/
	
	float VerticalScrollingLayer::GetScrollSpeed()
	{
		return layerScrollSpeed_;
	}
	
	/**************************************************************************/
	
	float VerticalScrollingLayer::GetTranslucency()
	{
		return translucency_;
	}
	
	/**************************************************************************/
	
	int VerticalScrollingLayer::GetWidth()
	{
		return layerWidth_;
	}
	
	/**************************************************************************/
	
	int VerticalScrollingLayer::GetHeight()
	{
		return layerHeight_;
	}
	
} // end namespace


