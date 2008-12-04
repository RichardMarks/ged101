
// CODESTYLE: v2.0

// Tileset.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage a list of pointers to the ImageResource class by name

/**
 * \file Tileset.h
 * \brief Tile-Based Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */

#ifndef __TILESET_H__
#define __TILESET_H__

namespace ENGINE
{
	// forward declare the classes we need
	class ImageResource;
	class ImageList;
	class NameDirectory;
	
	/**
	 * \class Tileset
	 * \brief A class to manage a list of pointers to the ImageResource class by name
	 * \ingroup TileBasedGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 *
	 * See the page \ref TileBasedExamplePage1 for an example of using the Tileset class
	 */
	class Tileset
	{
	public:
	
		/**
		 * default constructor
		 */
		Tileset();

		/**
		 * de-allocate any allocated memory by calling the Tileset::Destroy() function
		 */
		~Tileset();
		
		/**
		 * Adds a tile image to the tileset
		 * @param tileName is the name to give the tile
		 * @param image is the image to associate with the \a tileName
		 */
		void Add(const char* tileName, ImageResource* image);
		
		/**
		 * Adds several tile images to the tileset
		 * The tiles are named such that if you use "water" for the prefix, and 4 for the count,
		 * then you will have water0, water1, water2, water3 tiles added.
		 * @param tileNamePrefix is the prefix for the name that will be given to the added tile images
		 * @param count is the number of images that will be passed
		 * @param ... is the variable-argument-list of pointers to allocated instances of the ImageResource class
		 */
		void AddRange(const char* tileNamePrefix, unsigned int count, ...);
		
		/**
		 * Gets a tile image from the tileset
		 * @param tileName is the name of the tile to try to get
		 * \return a pointer to the image resource for the given name or 0 if none exists
		 */
		ImageResource* Get(const char* tileName);
		
		/**
		 * Gets a tile image from the tileset
		 * @param tileID is the tile ID to try to get
		 * \return a pointer to the image resource for the given tile ID or 0 if it does not exist
		 */
		ImageResource* Get(unsigned int tileID);

		/**
		 * Gets the tile ID for the given name
		 * @param tileName is the name of the tile to try to get
		 * \return the tile ID for the given name
		 */
		unsigned int GetIndex(const char* tileName);

		/**
		 * Gets the count of the tiles
		 * \return the number of tile images in the tileset
		 */
		unsigned int GetCount();

	private:
	
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * hidden copy constructor
		 */
		Tileset(const Tileset& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const Tileset& operator=(const Tileset& rhs);
		
		/**
		 * \var names_
		 * \brief lookup table for the tile image names
		 */
		NameDirectory* names_;
		
		/**
		 * \var images_
		 * \brief the list of images that are in the tileset
		 */
		ImageList* images_;
		
	}; // end class

} // end namespace
#endif


