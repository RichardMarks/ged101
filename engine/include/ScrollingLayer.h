
// CODESTYLE: v2.0

// ScrollingLayer.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A layer that can scroll an image in any direction at any speed

/**
 * \file ScrollingLayer.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __SCROLLINGLAYER_H__
#define __SCROLLINGLAYER_H__

#include "Vector.h"

#include "SceneLayer.h"

namespace ENGINE
{
	// forward declare the classes we need
	class ImageResource;
	
	/**
	 * \namespace SCROLLER
	 * \brief ScrollingLayer enumerations
	 */
	namespace SCROLLER
	{
		/**
		 * \enum ScrollType
		 * \brief possible scrolling types
		 */
		enum ScrollType
		{
			//! no scrolling will happen
			NoScroller,
			
			//! the layer will scroll on the X axis
			HorizontalScroller,
			
			//! the layer will scroll on the Y axis
			VerticalScroller,
			
			//! the layer will scroll on both the X and Y axes
			CombinationScroller
		};
	} // end namespace
	
	/**
	 * \class ScrollingLayer
	 * \brief A layer that can scroll an image in any direction at any speed
	 * \ingroup SceneGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class ScrollingLayer : public SceneLayer
	{
	public:
		ScrollingLayer();
		ScrollingLayer(ImageResource* image, float scrollSpeedX, float scrollSpeedY, float translucency = 1.0f);
		ScrollingLayer(const char* imageFileName, float scrollSpeedX, float scrollSpeedY, float translucency = 1.0f);
		virtual ~ScrollingLayer();
		
		/**
		 * Initializes the data for the layer
		 */
		virtual bool Initialize();
		
		/**
		 * Initializes the data for the layer
		 */
		virtual void Update(float deltaTime);
		
		/**
		 * Renders the layer to \a target
		 * @param target is the image to render the layer to
		 */
		virtual void Render(ImageResource* target);
		
		/**
		 * De-allocates the data for the layer
		 */
		virtual void Destroy();
		
		void SetImage(ImageResource* image);
		void SetImage(const char* imageFileName);
		void SetScrollSpeed(float scrollSpeedX, float scrollSpeedY);
		void SetHorizontalScrollSpeed(float scrollSpeed);
		void SetVerticalScrollSpeed(float scrollSpeed);
		void SetTranslucency(float translucency = 1.0f);
		void SetPosition(float x, float y);
		
		ImageResource* GetImage();
		float GetHorizontalScrollSpeed();
		float GetVerticalScrollSpeed();
		float GetTranslucency();
		
	protected:
		
		// isolated render functions
		#if 0
		void RenderStatic(ImageResource* target);
		void RenderHorizontalScroller(ImageResource* target);
		void RenderVerticalScroller(ImageResource* target);
		void RenderCombinationScroller(ImageResource* target);
		
		
		typedef void (ScrollingLayer::*ScrollingLayerFuncDeclare)(ImageResource*);
		typedef struct ScrollingLayerFunc_Type 
		{ 
			ScrollingLayerFuncDeclare source_; 
		} ScrollingLayerFunc, *ScrollingLayerFuncPtr;
		ScrollingLayerFunc* renderFunction_;
		#endif
		
		FloatVector2D layerPosition_;
		FloatVector2D layerScrollSpeed_;
		float translucency_;
		SCROLLER::ScrollType scrollType_;
	}; // end class

} // end namespace
#endif


