
// CODESTYLE: v2.0

// VerticalScrollingLayer.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A layer that holds a single image, and can scroll either up or down

/**
 * \file VerticalScrollingLayer.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __VerticalSCROLLINGLAYER_H__
#define __VerticalSCROLLINGLAYER_H__

#include "Vector.h"

#include "SceneLayer.h"

namespace ENGINE
{
	// forward declare the classes we need
	class ImageResource;
	
	/**
	 * \class VerticalScrollingLayer
	 * \brief A layer that holds a single image, and can scroll either up or down
	 * \ingroup SceneGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class VerticalScrollingLayer : public SceneLayer
	{
	public:
		/**
		 * constructor
		 */
		VerticalScrollingLayer();
		
		/**
		 * alternate constructor
		 */
		VerticalScrollingLayer(ImageResource* image, float scrollSpeed, float translucency = 1.0f, float x = 0.0f, float y = 0.0f);
		
		/**
		 * alternate constructor
		 */
		VerticalScrollingLayer(const char* imageFileName, float scrollSpeed, float translucency = 1.0f, float x = 0.0f, float y = 0.0f);
		
		/**
		 * destructor
		 */
		virtual ~VerticalScrollingLayer();
		
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


