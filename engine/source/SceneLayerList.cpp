
// CODESTYLE: v2.0

// SceneLayerList.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to hold a list of pointers to the SceneLayer class

/**
 * \file SceneLayerList.cpp
 * \brief Scene Management Module - Implementation
 * \ingroup SceneGroup
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the complementing header
#include "SceneLayerList.h"

// include the scene layer header
#include "SceneLayer.h"

namespace ENGINE
{
	SceneLayerList::SceneLayerList()
	{
	}
	
	/**************************************************************************/
	
	SceneLayerList::~SceneLayerList()
	{
		Destroy();
	}
	
	/**************************************************************************/
	
	void SceneLayerList::Add(SceneLayer* layer)
	{
		layers_.push_back(layer);
	}
	
	/**************************************************************************/
	
	SceneLayer* SceneLayerList::Get(unsigned int index)
	{
		return (index < layers_.size()) ? layers_.at(index) : 0;
	}
	
	/**************************************************************************/
	
	unsigned int SceneLayerList::GetCount()
	{
		return static_cast<unsigned int>(layers_.size());
	}
	
	/**************************************************************************/
	
	void SceneLayerList::Clear()
	{
		Destroy();
	}
	
	/**************************************************************************/
	
	void SceneLayerList::Update(float deltaTime)
	{
		unsigned int index = 0;
		for (index = 0; index < layers_.size(); index++)
		{
			if (0 != layers_[index])
			{
				layers_[index]->Update(deltaTime);
			}
		}
	}
	
	/**************************************************************************/
	
	void SceneLayerList::Render(ImageResource* target)
	{
		unsigned int index = 0;
		for (index = 0; index < layers_.size(); index++)
		{
			if (0 != layers_[index])
			{
				layers_[index]->Render(target);
			}
		}
	}
	
	/**************************************************************************/
		
	void SceneLayerList::Destroy()
	{
		// delete all layers
		unsigned int index = 0;
		for (index = 0; index < layers_.size(); index++)
		{
			if (0 != layers_[index])
			{
				delete layers_[index];
				layers_[index] = 0;
			}
		}
		layers_.clear();
	}
	
} // end namespace


