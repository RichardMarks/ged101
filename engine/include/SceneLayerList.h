
// CODESTYLE: v2.0

// SceneLayerList.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a list of pointers to the SceneLayer class

/**
 * \file SceneLayerList.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __SCENELAYERLIST_H__
#define __SCENELAYERLIST_H__

#include <vector>

namespace ENGINE
{
	// forward declare the classes we need
	class SceneLayer;
	class ImageResource;
	
	/**
	 * \class SceneLayerList
	 * \brief A class to hold a list of pointers to the SceneLayer class
	 * \ingroup SceneGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class SceneLayerList
	{
	public:
		
		SceneLayerList();
		~SceneLayerList();
		void Add(SceneLayer* layer);
		SceneLayer* Get(unsigned int index);
		
		unsigned int GetCount();
		void Clear();
		
		void Update(float deltaTime);
		void Render(ImageResource* target);
		
	private:
		
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * hidden copy constructor
		 */
		SceneLayerList(const SceneLayerList& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const SceneLayerList& operator=(const SceneLayerList& rhs);
		
		/**
		 * \var layers_
		 * \brief an STL vector of pointers to the SceneLayer class
		 */
		std::vector<SceneLayer*> layers_;
	}; // end class

} // end namespace
#endif


