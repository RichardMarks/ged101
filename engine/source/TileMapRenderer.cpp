
// CODESTYLE: v2.0

// TileMapRenderer.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class for rendering a TileMap onto an ImageResource using an Tileset

/**
 * \file TileMapRenderer.cpp
 * \brief Tile-Based Module - Implementation
 */

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// include the complementing header
#include "TileMapRenderer.h"

// include the tileset header
#include "Tileset.h"

// include the tile header
#include "Tile.h"

// include the tile map header
#include "TileMap.h"

// include the image resource header
#include "ImageResource.h"

// include the error reporting header
#include "DebugReport.h"

namespace ENGINE
{
	TileMapRenderer() :
		tileMap_(0),
		tileSet_(0),
		renderTarget_(0)
	{
	}
	
	/**************************************************************************/
	
	TileMapRenderer::TileMapRenderer(TileMap* tileMap, Tileset* tileSet, ImageResource* target)
	{
		SetTileMap(tileMap);
		SetTileset(tileSet);
		SetRenderTarget(target);
		
		int targetWidth 	= renderTarget_->GetWidth();
		int targetHeight 	= renderTarget_->GetHeight();
		
		int mapWidth 		= tileMap_->GetWidth();
		int mapHeight 		= tileMap_->GetHeight();
		
		int tileWidth 		= tileSet_[0]->GetWidth();
		int tileHeight 		= tileSet_[0]->GetHeight();
		
		if ((targetWidth < (mapWidth * tileWidth)) || (targetHeight < (mapHeight * tileHeight)))
		{
			LogWarning(
				"The render target is not large enough to contain the entire tile map!\n"
				"Render Target is %d x %d\n"
				"Tile Map is %d x %d\n"
				"Tile size is %d x %d\n", 
				targetWidth, targetHeight, mapWidth, mapHeight, tileWidth, tileHeight);
		}
	}
	
	/**************************************************************************/
	
	TileMapRenderer::~TileMapRenderer()
	{
		// nothing is allocated, and its up to the called to destroy the allocated tile map, tileset, and render target!
	}
	
	/**************************************************************************/
	
	void TileMapRenderer::SetTileMap(TileMap* tileMap)
	{
		tileMap_ = tileMap;
	}
	
	/**************************************************************************/
	
	void TileMapRenderer::SetTileset(Tileset* tileSet)
	{
		tileSet_ = tileSet;
	}
	
	void TileMapRenderer::SetRenderTarget(ImageResource* target)
	{
		renderTarget_ = target;
	}
	
	/**************************************************************************/
	
	void TileMapRenderer::Render()
	{
		int mapWidth 	= tileMap_->GetWidth();
		int mapHeight 	= tileMap_->GetHeight();
		int tileWidth 	= tileSet_[0]->GetWidth();
		int tileHeight 	= tileSet_[0]->GetHeight();
		
		for (int row = 0; row < mapHeight; row++)
		{
			for (int column = 0; column < mapWidth; column++)
			{
				int x = column * tileWidth;
				int y = row * tileHeight;
				
				Tile* tile = tileMap_->GetTile(column, row);
				
				unsigned int tileValue = tile->GetValue();
				
				tileSet_[tileValue]->Blit(renderTarget_, 0, 0, x, y, tileWidth, tileHeight);
			}
		} 
	}
	
} // end namespace


