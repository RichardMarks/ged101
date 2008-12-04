
// CODESTYLE: v2.0

// Tile.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A basic tile for creating simple single-layer tile maps

/**
 * \file Tile.cpp
 * \brief Tile-Based Module - Implementation
 * \author Richard Marks <ccpsceo@gmail.com>
 */

// include the complementing header
#include "Tile.h"

namespace ENGINE
{
	Tile::Tile() :
		tileValue_(0),
		tileSolid_(false)
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	Tile::Tile(unsigned int value, bool isSolid)
	{
		tileValue_ = value;
		tileSolid_ = isSolid;
	}
	
	/**************************************************************************/
	
	Tile::~Tile()
	{
		// implement class destructor here
		Destroy();
	} // end destructor
	
	/**************************************************************************/
	
	void Tile::SetValue(unsigned int value)
	{
		tileValue_ = value;
	}
	
	/**************************************************************************/
	
	void Tile::SetSolid(bool isSolid)
	{
		tileSolid_ = isSolid;
	}
	
	/**************************************************************************/
	
	void Tile::Clone(Tile* source)
	{
		tileValue_ = source->tileValue_;
		tileSolid_ = source->tileSolid_;
	}
	
	/**************************************************************************/
	
	unsigned int Tile::GetValue()
	{
		return tileValue_;
	}
	
	/**************************************************************************/
	
	bool Tile::IsSolid()
	{
		return tileSolid_;
	}
	
	/**************************************************************************/
	
	void Tile::Destroy()
	{
		// the default implementation does not need to do anything
	}

} // end namespace


