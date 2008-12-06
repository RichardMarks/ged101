
// CODESTYLE: v2.0

// SceneLayer.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: The base class that all Scene Layer types inherit from

/**
 * \file SceneLayer.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __SCENELAYER_H__
#define __SCENELAYER_H__

namespace ENGINE
{
	// forward declare the classes we need
	class ImageResource;
	
	/**
	 * \class SceneLayer
	 * \brief The base class that all Scene Layer types inherit from
	 * \ingroup SceneGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class SceneLayer
	{
	public:
	
		/**
		 * default constructor
		 */
		SceneLayer();
		
		/**
		 * deconstructor
		 */
		virtual ~SceneLayer();
		
		/**
		 * Initializes the data for the layer
		 * pure-virtual. must be implemented in an inherited class
		 */
		virtual bool Initialize() = 0;
		
		/**
		 * Initializes the data for the layer
		 * pure-virtual. must be implemented in an inherited class
		 */
		virtual void Update(float deltaTime) = 0;
		
		/**
		 * Renders the layer to \a target
		 * pure-virtual. must be implemented in an inherited class
		 * @param target is the image to render the layer to
		 */
		virtual void Render(ImageResource* target) = 0;
		
		/**
		 * De-allocates the data for the layer
		 * pure-virtual. must be implemented in an inherited class
		 */
		virtual void Destroy() = 0;
		
	protected:
	
		/**
		 * \var drawingSurface_
		 * \brief the image that holds anything that will be rendered for the layer
		 */
		ImageResource* drawingSurface_;
	}; // end class

} // end namespace
#endif


