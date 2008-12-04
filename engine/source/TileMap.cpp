
// CODESTYLE: v2.0

// TileMap.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A basic tile map for creating simple single-layer tile maps

/**
 * \file TileMap.cpp
 * \brief Tile-Based Module - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// include the complementing header
#include "TileMap.h"

// include the tile header
#include "Tile.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	TileMap::TileMap() :
		tiles_(0),
		mapWidth_(0),
		mapHeight_(0)
	{
		// implement class constructor here
	} // end constructor

	/**************************************************************************/
	
	TileMap::TileMap(int width, int height)
	{
		tiles_ = 0;
		SetSize(width, height);
	}
	
	/**************************************************************************/
	
	TileMap::~TileMap()
	{
		// implement class destructor here
		Destroy();
	} // end destructor
	
	/**************************************************************************/
	
	void TileMap::SetTile(int x, int y, Tile* tile)
	{
		int index = x + (y * mapWidth_);
		
		if (index > (mapWidth_ * mapHeight_))
		{
			LogWarning("Tile Index out of bounds: (%d, %d) = Index %d", x, y, index);
			return;
		}
		
		if (0 != tiles_[index])
		{
			tiles_[index]->Clone(tile);
		}
	}
	
	/**************************************************************************/
	
	void TileMap::SetSize(int width, int height)
	{
		// wipe out the existing tile map
		Destroy();
		
		mapWidth_ = width;
		mapHeight_ = height;
		
		int tileCount = (mapWidth_ * mapHeight_);
		
		tiles_ = new Tile* [tileCount];
		
		for (int index = 0; index < tileCount; index++)
		{
			tiles_[index] = new Tile(0, false);
		}
	}
	
	/**************************************************************************/
	
	Tile* TileMap::GetTile(int x, int y)
	{
		int index = x + (y * mapWidth_);
		
		if (index > (mapWidth_ * mapHeight_))
		{
			LogWarning("Tile Index out of bounds: (%d, %d) = Index %d", x, y, index);
			return 0;
		}
		
		if (0 != tiles_[index])
		{
			return tiles_[index];
		}
	}
	
	/**************************************************************************/
	
	int TileMap::GetWidth()
	{
		return mapWidth_;
	}
	
	/**************************************************************************/
	
	int TileMap::GetHeight()
	{
		return mapHeight_;
	}
	
	/**************************************************************************/
	
	void TileMap::Destroy()
	{
		if (0 != tiles_)
		{
			int tileCount = (mapWidth_ * mapHeight_);
		
			for (int index = 0; index < tileCount; index++)
			{
				if (0 != tiles_[index])
				{
					delete tiles_[index];
					tiles_[index] = 0;
				}
			}
			delete [] tiles_;
			tiles_ = 0;
			mapWidth_ = 0;
			mapHeight_ = 0;
		}
	}

} // end namespace


