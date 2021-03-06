
// CODESTYLE: v2.0

// Tile.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A basic tile for creating simple single-layer tile maps

/**
 * \file Tile.h
 * \brief Tile-Based Module - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */
 
#ifndef __TILE_H__
#define __TILE_H__

namespace ENGINE
{
	/**
	 * \class Tile
	 * \brief A basic tile for creating simple single-layer tile maps
	 * \ingroup TileBasedGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 *
	 * This class serves as a base class for more complex tile types to create advanced tile maps
	 * \sa ENGINE::LayeredTile
	 */
	class Tile
	{
	public:
		
		/**
		 * default constructor
		 */
		Tile();
		
		/**
		 * alternate constructor, initializes the tile
		 * @param value is a value between 0 and 65535 to specify what value the tile has
		 * @param isSolid is a boolean that lets you specify if the tile is solid or not. Default is false
		 */
		Tile(unsigned int value, bool isSolid = false);

		/**
		 * virtual deconstructor calls Tile::Destroy()
		 */
		virtual ~Tile();
		
		/**
		 * Sets the value for the tile
		 * @param value is a value between 0 and 65535 to specify what value the tile has
		 */
		void SetValue(unsigned int value);
		
		/**
		 * Sets the solidness of the tile
		 * @param isSolid is a boolean that lets you specify if the tile is solid or not. Default is true
		 */
		void SetSolid(bool isSolid = true);
		
		/**
		 * Clones the properties of another tile
		 * @param source is a pointer to the ENGINE::Tile structure to clone from
		 */
		 void Clone(Tile* source);
		
		/**
		 * Gets the value of the tile
		 * \return an unsigned integer value between 0 and 65535 
		 */
		unsigned int GetValue();
		
		/**
		 * Gets the solidness of the tile
		 * \return true if the tile is solid, and false if it is not
		 */
		bool IsSolid();
		
	protected:
	
		/**
		 * called by the destructor
		 */
		virtual void Destroy();
		
		/**
		 * \var tileValue_
		 * \brief an unsigned integer value between 0 and 65535 
		 */
		unsigned int tileValue_;
	
		/**
		 * \var tileSolid_
		 * \brief true if the tile is solid, and false if it is not
		 */
		bool tileSolid_;
	
	private:
		/**
		 * hidden copy constructor -- we don't want copies being made. Use the Tile::Clone() function
		 */
		Tile(const Tile& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const Tile& operator=(const Tile& rhs);
	}; // end class

} // end namespace
#endif


