
// CODESTYLE: v2.0

// TileMap.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A basic tile map for creating simple single-layer tile maps

/**
 * \file TileMap.h
 * \brief Tile-Based Map Module - Header
 */
 
#ifndef __TILEMAP_H__
#define __TILEMAP_H__

namespace ENGINE
{
	// forward declare the classes we need
	class Tile;
	
	/**
	 * \class TileMap
	 * \brief A basic tile map for creating simple single-layer tile maps
	 *
	 * This class serves as a base class for more advanced tile maps
	 * \sa ENGINE::LayeredTileMap
	 */
	class TileMap
	{
	public:
		
		/**
		 * default constructor
		 */
		TileMap();
		
		/**
		 * alternate constructor, initializes the tile map
		 */
		TileMap(int width, int height);

		/**
		 * virtual deconstructor calls TileMap::Destroy()
		 */
		virtual ~TileMap();
		
		/**
		 * Sets a tile
		 * @param x is the X coordinate to set the tile in tiles
		 * @param y is the Y coordiante to set the tile in tiles
		 * @param tile is a pointer to an ENGINE::Tile structure to place on the tile map
		 */
		void SetTile(int x, int y, Tile* tile);
		
		/**
		 * Sets the size of the tile map
		 * This function will erase the existing tile map if there is any.
		 * This function allocates the memory and sets all tiles to a default value of 0, non-solid.
		 * @param width is the width of the tile map in tiles
		 * @param height is the height of the tile map in tiles
		 */
		void SetSize(int width, int height);
		
		/**
		 * Gets a tile
		 * @param x is the X coordinate to get the tile from in tiles
		 * @param y is the Y coordiante to get the tile from in tiles
		 * \return a pointer to the ENGINE::Tile structure at the coordinate specified or 0 if the coordinate is invalid
		 */
		Tile* GetTile(int x, int y);
		
		/**
		 * Gets the width of the tile map
		 * \return the width of the tile map in tiles
		 */
		int GetWidth();
		
		/**
		 * Gets the height of the tile map
		 * \return the height of the tile map in tiles
		 */
		int GetHeight();
		
	protected:
	
		/**
		 * called by the destructor
		 */
		virtual void Destroy();
		
		/**
		 * \var tiles_
		 * \brief an array of pointers to ENGINE::Tile structures
		 */
		Tile** tiles_;
		
		/**
		 * \var mapWidth_
		 * \brief the width of the tile map in tiles
		 */
		int mapWidth_;
		
		/**
		 * \var mapHeight_
		 * \brief the height of the tile map in tiles
		 */
		int mapHeight_;
	
	}; // end class

} // end namespace
#endif


