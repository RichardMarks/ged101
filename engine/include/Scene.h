
// CODESTYLE: v2.0

// Scene.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A singleton class to manage the current scene

/**
 * \file Scene.h
 * \brief Scene Management Module - Header
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __SCENE_H__
#define __SCENE_H__

namespace ENGINE
{
	// forward declare the classes we need
	class SceneLayer;
	class SceneLayerList;
	class NameDirectory;
	class ImageResource;
	
	/**
	 * \class SceneSingleton
	 * \brief A singleton class to manage the current scene
	 * \ingroup SceneGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class SceneSingleton
	{
	public:
	
		static SceneSingleton* GetInstance();
		~SceneSingleton();
		
		void AddLayer(const char* layerName, SceneLayer* layer);
		SceneLayer* GetLayer(const char* layerName);
		
		void Update(float deltaTime);
		void Render(ImageResource* target);
		
	private:
	
		void Destroy();
		SceneSingleton();
		SceneSingleton(const SceneSingleton& rhs);
		const SceneSingleton& operator=(const SceneSingleton& rhs);
		
		NameDirectory* names_;
		SceneLayerList* layers_;
	}; // end class

} // end namespace
#endif


