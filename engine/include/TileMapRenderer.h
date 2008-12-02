
// CODESTYLE: v2.0

// TileMapRenderer.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class for rendering a TileMap onto an ImageResource using an Tileset

/**
 * \file TileMapRenderer.h
 * \brief Tile-Based Module - Header
 */

#ifndef __TILEMAPRENDERER_H__
#define __TILEMAPRENDERER_H__

namespace ENGINE
{
	// forward declare the classes we need
	class TileMap;
	class Tileset;
	class ImageResource;
	
	/**
	 * \class TileMapRenderer
	 * \brief A class for rendering a TileMap onto an ImageResource using an Tileset
	 *
	 * Also serves as a base-class for implementing more complex renderers.
	 * See the page \ref TileBasedExamplePage1 for an example of using the TileMapRenderer class
	 */
	class TileMapRenderer
	{
	public:
	
		/**
		 * default constructor
		 */
		TileMapRenderer();
		
		/**
		 * alternate constructor to initialize all properties of the class at once
		 */
		TileMapRenderer(TileMap* tileMap, Tileset* tileSet, ImageResource* target);
		
		/**
		 * default deconstructor -- you should never need to allocate and 
		 * therefore de-allocate anything in this class
		 */
		virtual ~TileMapRenderer();
		
		/**
		 * Sets the tilemap
		 * @param tileMap is the tilemap to render
		 */
		void SetTileMap(TileMap* tileMap);
		
		/**
		 * Sets the tileset
		 * @param tileSet is the tileset with which to render
		 */
		void SetTileset(Tileset* tileSet);
		
		/**
		 * Sets the render target
		 * @param target is the image buffer onto which the map is to be rendered
		 */
		void SetRenderTarget(ImageResource* target);
		
		/**
		 * a default rendering function
		 * override this to perform more complex rendering than just 
		 * blitting the whole map to the render target
		 */
		virtual void Render();
		
	protected:
	
		/**
		 * \var tileMap_
		 * \brief the tilemap to render
		 */
		TileMap* tileMap_;
		
		/**
		 * \var tileSet_
		 * \brief the tileset with which to render
		 */
		Tileset* tileSet_;
		
		/**
		 * \var renderTarget_
		 * \brief the image buffer onto which the map is to be rendered
		 */
		ImageResource* renderTarget_;
	
	private:
		
		/**
		 * hidden copy constructor
		 */
		TileMapRenderer(const TileMapRenderer& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const TileMapRenderer& operator=(const TileMapRenderer& rhs);
	}; // end class

} // end namespace
#endif


