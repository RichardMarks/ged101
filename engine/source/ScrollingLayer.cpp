
// CODESTYLE: v2.0

// ScrollingLayer.cpp
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
#include "ScrollingLayer.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	ScrollingLayer::ScrollingLayer() :
		translucency_(1.0f)//,
		//renderFunction_(0)
	{
	}
	
	/**************************************************************************/
	
	ScrollingLayer::ScrollingLayer(ImageResource* image, float scrollSpeedX, float scrollSpeedY, float translucency)
	{
		SetPosition(0.0f, 0.0f);
		SetScrollSpeed(scrollSpeedX, scrollSpeedY);
		SetTranslucency(translucency);
		SetImage(image);
		//renderFunction_			= 0;
	}
	
	/**************************************************************************/
	
	ScrollingLayer::ScrollingLayer(const char* imageFileName, float scrollSpeedX, float scrollSpeedY, float translucency)
	{
		SetPosition(0.0f, 0.0f);
		SetScrollSpeed(scrollSpeedX, scrollSpeedY);
		SetTranslucency(translucency);
		SetImage(imageFileName);
		//renderFunction_			= 0;
	}
	
	/**************************************************************************/
		
	ScrollingLayer::~ScrollingLayer()
	{
		Destroy();
#if 0
		if (0 != renderFunction_)
		{
			delete renderFunction_;
		}
#endif
	}
	
	/**************************************************************************/
#if 0
	bool ScrollingLayer::Initialize()
	{
		if (0 == image)
		{
			LogWarning("No image was set for the layer. Use SetImage() to remedy this.");
			return false;
		}
		
		// we only need to create the render function the first time
		static firstCall = true;
		if (firstCall)
		{
			if (0 == renderFunction_)
			{
				renderFunction_ = new ScrollingLayerFunc;
			}
			firstCall = false;
		}
		
		int imageWidth = drawingSurface_->GetWidth();
		int imageHeight = drawingSurface_->GetHeight();
		
		// what type of scrolling will this layer be doing if any
		int scrollType = 1;
		
		if (layerScrollSpeed_[0] > 0.0f)
		{
			scrollType += 2;
		}
		
		if (layerScrollSpeed_[1] > 0.0f)
		{
			scrollType += 4;
		}
		
		// set the rendering function accordingly
		switch(scrollType)
		{
			// layer does not scroll
			case 1:
			{
				renderFunction_->source_ = &ScrollingLayer::RenderStatic;
			} break;
			
			// layer scrolls horizontally
			case 3: 
			{
				renderFunction_->source_ = &ScrollingLayer::RenderHorizontalScroller;
				
				// horizontal scrolling means we need to have a layer image blit 3 times
				// [1][2][3]
				
				ImageResource* temp = new ImageResource(imageWidth, imageHeight);
				drawingSurface_->Blit(temp, 0, 0, 0, 0, imageWidth, imageHeight);
				delete drawingSurface_;
				drawingSurface_ = new ImageResource(imageWidth * 3, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, 0, 0, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth, 0, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth * 2, 0, imageWidth, imageHeight);
				delete temp;
				
			} break;
			
			// layer scrolls vertically
			case 5: 
			{
				renderFunction_->source_ = &ScrollingLayer::RenderVerticalScroller;
				
				// vertical scrolling means we need to have a layer image blit 3 times
				// [1]
				// [2]
				// [3]
				ImageResource* temp = new ImageResource(imageWidth, imageHeight);
				drawingSurface_->Blit(temp, 0, 0, 0, 0, imageWidth, imageHeight);
				delete drawingSurface_;
				drawingSurface_ = new ImageResource(imageWidth, imageHeight * 3);
				temp->Blit(drawingSurface_, 0, 0, 0, 0, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, 0, imageHeight, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, 0, imageHeight * 2, imageWidth, imageHeight);
				delete temp;
				
			} break;
			
			// layer scrolls both horizontally and vertically
			case 8:
			{
				renderFunction_->source_ = &ScrollingLayer::RenderCombinationScroller;
				
				// combination scrolling means we need the blit the layer image 9 times
				// [0][1][2]
				// [3][4][5]
				// [6][7][8]
				ImageResource* temp = new ImageResource(imageWidth, imageHeight);
				drawingSurface_->Blit(temp, 0, 0, 0, 0, imageWidth, imageHeight);
				delete drawingSurface_;
				drawingSurface_ = new ImageResource(imageWidth * 3, imageHeight * 3);
				temp->Blit(drawingSurface_, 0, 0, 0, 0, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth, 0, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth * 2, 0, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, 0, imageHeight, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth, imageHeight, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth * 2, imageHeight, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, 0, imageHeight * 2, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth, imageHeight * 2, imageWidth, imageHeight);
				temp->Blit(drawingSurface_, 0, 0, imageWidth * 2, imageHeight * 2, imageWidth, imageHeight);
				delete temp;
			}
		}
		
		return true;
	}
#endif
	
	bool ScrollingLayer::Initialize()
	{
		if (0 == drawingSurface_)
		{
			LogWarning("No image was set for the layer. Use SetImage() to remedy this.");
			return false;
		}
		
		// save the original image
		// because the image will be changed any time the scrolling type changes
		static ImageResource* originalLayerImage = 0;
		static bool firstCall = true;
		if (firstCall)
		{
			
			int imageWidth = drawingSurface_->GetWidth();
			int imageHeight = drawingSurface_->GetHeight();
		
			originalLayerImage = new ImageResource(imageWidth, imageHeight);
			drawingSurface_->Blit(originalLayerImage, 0, 0, 0, 0, imageWidth, imageHeight);
			firstCall = false;
		}
		
		// what type of scrolling will this layer be doing if any
		SCROLLER::ScrollType nextScrollType;
		
		if (layerScrollSpeed_[0] == 0.0f && layerScrollSpeed_[1] == 0.0f)
		{
			nextScrollType = SCROLLER::NoScroller;
		}
		else if (layerScrollSpeed_[0] > 0.0f && layerScrollSpeed_[1] == 0.0f)
		{
			nextScrollType = SCROLLER::HorizontalScroller;
		}
		else if (layerScrollSpeed_[1] > 0.0f && layerScrollSpeed_[0] == 0.0f)
		{
			nextScrollType = SCROLLER::VerticalScroller;
		}
		else
		{
			nextScrollType = SCROLLER::CombinationScroller;
		}
		
		// if the current scroll type is not the same as the next scroll type
		if (nextScrollType != scrollType_)
		{
			
			int imageWidth = originalLayerImage->GetWidth();
			int imageHeight = originalLayerImage->GetHeight();
		
			// rebuild the layer's image as we need it to be
			switch(nextScrollType)
			{
				case SCROLLER::NoScroller: 
				{
					delete drawingSurface_;
					drawingSurface_ = new ImageResource(imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, 0, imageWidth, imageHeight);
				} break;
				
				case SCROLLER::HorizontalScroller: 
				{
					// horizontal scrolling means we need to have a layer image blit 3 times along the X axis
					// [1][2][3]
					delete drawingSurface_;
					drawingSurface_ = new ImageResource(imageWidth * 3, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, 0, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth, 0, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth * 2, 0, imageWidth, imageHeight);

				} break;
				
				case SCROLLER::VerticalScroller: 
				{
					// vertical scrolling means we need to have a layer image blit 3 times along the Y axis
					// [1]
					// [2]
					// [3]
					delete drawingSurface_;
					drawingSurface_ = new ImageResource(imageWidth, imageHeight * 3);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, 0, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, imageHeight, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, imageHeight * 2, imageWidth, imageHeight);

				} break;
				
				case SCROLLER::CombinationScroller: 
				{
					// combination scrolling means we need the blit the layer image 9 times to form a grid
					// [0][1][2]
					// [3][4][5]
					// [6][7][8]
					delete drawingSurface_;
					drawingSurface_ = new ImageResource(imageWidth * 3, imageHeight * 3);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, 0, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth, 0, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth * 2, 0, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, imageHeight, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth, imageHeight, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth * 2, imageHeight, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, 0, imageHeight * 2, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth, imageHeight * 2, imageWidth, imageHeight);
					originalLayerImage->Blit(drawingSurface_, 0, 0, imageWidth * 2, imageHeight * 2, imageWidth, imageHeight);

				} break;
			}
		}
		
		return true;
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::Update(float deltaTime)
	{
		if (SCROLLER::NoScroller == scrollType_)
		{
			// we don't update the layer's position since the layer does not move there is no point.
			return;
		}
		
		layerPosition_ += layerScrollSpeed_ * deltaTime;
	}
	
	/**************************************************************************/

	void ScrollingLayer::Render(ImageResource* target)
	{
		int x = static_cast<int>(layerPosition_[0]);
		int y = static_cast<int>(layerPosition_[1]);
		
		// are we drawing this thing with translucency
		if (translucency_ < 1.0f)
		{
			drawingSurface_->BlitAlpha(target, x, y, translucency_);
			return;
		}
		
		// or are we drawing this thing opaque
		int w = drawingSurface_->GetWidth();
		int h = drawingSurface_->GetHeight();
		
		drawingSurface_->BlitMasked(target, 0, 0, x, y, w, h);
	}

#if 0
	void ScrollingLayer::Render(ImageResource* target)
	{
		if (0 != renderFunction_)
		{
			if (0 != renderFunction_->source_)
			{
				(this->*renderFunction_->source_)(target);
				return;
			}
			else
			{
				LogWarning("Rendering Function Source was Never set. Weird BUG?");
			}
		}
		else
		{
			LogWarning("Rendering Function is invalid. Did you forget to Initialize() the layer?");
		}
	}
	
	/**************************************************************************/

	void ScrollingLayer::RenderStatic(ImageResource* target)
	{
		int x = static_cast<int>(layerPosition_[0]);
		int y = static_cast<int>(layerPosition_[1]);
		
		// are we drawing this thing with translucency
		if (translucency_ < 1.0f)
		{
			drawingSurface_->BlitAlpha(target, x, y, translucency_);
			return;
		}
		
		// or are we drawing this thing opaque
		int w = drawingSurface_->GetWidth();
		int h = drawingSurface_->GetHeight();
		
		drawingSurface_->BlitMasked(target, 0, 0, x, y, w, h);
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::RenderHorizontalScroller(ImageResource* target)
	{
		int x = static_cast<int>(layerPosition_[0]);
		int y = static_cast<int>(layerPosition_[1]);
		int w = drawingSurface_->GetWidth();
		int h = drawingSurface_->GetHeight();
		
		// are we drawing this thing with translucency
		if (translucency_ < 1.0f)
		{
			drawingSurface_->BlitAlpha(target, x, y, translucency_);
			drawingSurface_->BlitAlpha(target, x - w, y, translucency_);
			drawingSurface_->BlitAlpha(target, x + w, y, translucency_);
			return;
		}
		
		drawingSurface_->BlitMasked(target, 0, 0, x, y, w, h);
		drawingSurface_->BlitMasked(target, 0, 0, x - w, y, w, h);
		drawingSurface_->BlitMasked(target, 0, 0, x + w, y, w, h);
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::RenderVerticalScroller(ImageResource* target)
	{
		int x = static_cast<int>(layerPosition_[0]);
		int y = static_cast<int>(layerPosition_[1]);
		int w = drawingSurface_->GetWidth();
		int h = drawingSurface_->GetHeight();
		
		// are we drawing this thing with translucency
		if (translucency_ < 1.0f)
		{
			drawingSurface_->BlitAlpha(target, x, y, translucency_);
			
			return;
		}
		
		drawingSurface_->BlitMasked(target, 0, 0, x, y, w, h);
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::RenderCombinationScroller(ImageResource* target)
	{
		int x = static_cast<int>(layerPosition_[0]);
		int y = static_cast<int>(layerPosition_[1]);
		int w = drawingSurface_->GetWidth();
		int h = drawingSurface_->GetHeight();
		
		// are we drawing this thing with translucency
		if (translucency_ < 1.0f)
		{
			drawingSurface_->BlitAlpha(target, x, y, translucency_);
			drawingSurface_->BlitAlpha(target, x, y - y, translucency_);
			drawingSurface_->BlitAlpha(target, x, y + h, translucency_);
			drawingSurface_->BlitAlpha(target, x - w, y, translucency_);
			drawingSurface_->BlitAlpha(target, x + w, y, translucency_);
			return;
		}
		
		drawingSurface_->BlitMasked(target, 0, 0, x, y, w, h);
	}
#endif

	/**************************************************************************/
	
	void ScrollingLayer::Destroy()
	{
		if (0 != drawingSurface_)
		{
			delete drawingSurface_;
			drawingSurface_ = 0;
		}
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::SetImage(ImageResource* image)
	{
		Destroy();
		if (0 == image)
		{
			LogWarning("setting layer image to an invalid image resource!");
		}
		drawingSurface_ = image;
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::SetImage(const char* imageFileName)
	{
		Destroy();
		drawingSurface_ = new ImageResource(imageFileName);
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::SetScrollSpeed(float scrollSpeedX, float scrollSpeedY)
	{
		layerScrollSpeed_[0] 	= scrollSpeedX;
		layerScrollSpeed_[1] 	= scrollSpeedY;
		
		Initialize();
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::SetHorizontalScrollSpeed(float scrollSpeed)
	{
		layerScrollSpeed_[0] 	= scrollSpeed;
		
		Initialize();
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::SetVerticalScrollSpeed(float scrollSpeed)
	{
		layerScrollSpeed_[1] 	= scrollSpeed;
		
		Initialize();
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::SetTranslucency(float translucency)
	{
		translucency_ = translucency;
	}
	
	/**************************************************************************/
	
	void ScrollingLayer::SetPosition(float x, float y)
	{
		layerPosition_[0] = x;
		layerPosition_[1] = y;
	}
	
	
	/**************************************************************************/
		
	ImageResource* ScrollingLayer::GetImage()
	{
		return drawingSurface_;
	}
	
	/**************************************************************************/
	
	float ScrollingLayer::GetHorizontalScrollSpeed()
	{
		return layerScrollSpeed_[0];
	}
	
	/**************************************************************************/
	
	float ScrollingLayer::GetVerticalScrollSpeed()
	{
		return layerScrollSpeed_[1];
	}
	
	/**************************************************************************/
	
	float ScrollingLayer::GetTranslucency()
	{
		return translucency_;
	}
	
} // end namespace


