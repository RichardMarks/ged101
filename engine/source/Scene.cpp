
// CODESTYLE: v2.0

// Scene.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A singleton class to manage the current scene

/**
 * \file Scene.cpp
 * \brief Scene Management Module - Implementation
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the complementing header
#include "Scene.h"

// include the scene layer header
#include "SceneLayer.h"

// include the scene layer list header
#include "SceneLayerList.h"

// include the name directory header
#include "NameDirectory.h"

// include the image resource header
#include "ImageResource.h"

namespace ENGINE
{
	SceneSingleton* SceneSingleton::GetInstance()
	{
		static SceneSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	void SceneSingleton::AddLayer(const char* layerName, SceneLayer* layer)
	{
		layers_->Add(layer);
		
		unsigned int count = static_cast<unsigned int>(layers_->GetCount() - 1);
		names_->Add(layerName, count);
	}
	
	/**************************************************************************/
	
	SceneLayer* SceneSingleton::GetLayer(const char* layerName)
	{
		return layers_->Get(names_->Get(layerName));
	}
	
	/**************************************************************************/
	
	void SceneSingleton::Update(float deltaTime)
	{
		layers_->Update(deltaTime);
	}
	
	/**************************************************************************/
	
	void SceneSingleton::Render(ImageResource* target)
	{
		layers_->Render(target);
	}
	
	/**************************************************************************/
	
	void SceneSingleton::Destroy()
	{
		if (0 != layers_)
		{
			delete layers_;
			layers_ = 0;
		}
		
		if (0 != names_)
		{
			delete names_;
			names_ = 0;
		}
	}
	
	/**************************************************************************/
	
	SceneSingleton::SceneSingleton()
	{
		layers_ = new SceneLayerList();
		names_ = new NameDirectory();
	}
	
	/**************************************************************************/
	
	SceneSingleton::~SceneSingleton()
	{
		Destroy();
	}
	
} // end namespace


