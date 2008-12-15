
// CODESTYLE: v2.0

// HorizontalScrollingLayer.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A layer that holds a single image, and can scroll either left or right

/**
 * \file HorizontalScrollingLayer.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __HORIZONTALSCROLLINGLAYER_H__
#define __HORIZONTALSCROLLINGLAYER_H__

#include "Vector.h"

#include "SceneLayer.h"

namespace ENGINE
{
	// forward declare the classes we need
	class ImageResource;
	
	/**
	 * \class HorizontalScrollingLayer
	 * \brief A layer that holds a single image, and can scroll either left or right
	 * \ingroup SceneGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class HorizontalScrollingLayer : public SceneLayer
	{
	public:
		/**
		 * constructor
		 */
		HorizontalScrollingLayer();
		
		/**
		 * alternate constructor
		 */
		HorizontalScrollingLayer(ImageResource* image, float scrollSpeed, float translucency = 1.0f, float x = 0.0f, float y = 0.0f);
		
		/**
		 * alternate constructor
		 */
		HorizontalScrollingLayer(const char* imageFileName, float scrollSpeed, float translucency = 1.0f, float x = 0.0f, float y = 0.0f);
		
		/**
		 * destructor
		 */
		virtual ~HorizontalScrollingLayer();
		
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
		void SetScrollSpeed(float scrollSpeed);
		void SetTranslucency(float translucency = 1.0f);
		void SetPosition(float x, float y);
		
		ImageResource* GetImage();
		float GetScrollSpeed();
		float GetTranslucency();
		int GetWidth();
		int GetHeight();
		
	protected:
		FloatVector2D layerPosition_;
		float layerScrollSpeed_;
		float translucency_;
		int layerWidth_;
		int layerHeight_;
	}; // end class

} // end namespace
#endif


