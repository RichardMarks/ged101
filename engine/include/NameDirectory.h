
// CODESTYLE: v2.0

// NameDirectory.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class to manage a directory of names for using simple name/index lookup tables

/**
 * \file NameDirectory.h
 * \brief Generic Utility System Module - Header
 */

#ifndef __NAMEDIRECTORY_H__
#define __NAMEDIRECTORY_H__

#include <vector>
#include <map>
#include <string>

namespace ENGINE
{
	/**
	 * \class NameDirectory
	 * \brief A class to manage a directory of names for using simple name/index lookup tables
	 */
	class NameDirectory
	{
	public:
		
		/**
		 * default constructor
		 */
		NameDirectory();
		
		/**
		 * De-allocates any allocated memory by calling NameDirectory::Destroy()
		 */
		~NameDirectory();
		
		/**
		 * Add a name to the directory
		 * @param name is the name to add
		 * @param value is the value to associate with the name
		 * \return the index number of the added name
		 */
		void Add(const char* name, unsigned int value);
		
		/**
		 * Gets the lookup value for the name
		 * @param name is the name to look up
		 * \return the value associated with the name
		 */
		unsigned int Get(const char* name);
		
	private:
	
		void Destroy();
		
		//! STL map of string to unsigned ints for keeping a lookup table
		typedef std::map<std::string, unsigned int> LUT;
		
		//! STL iterator for a map of string to uints
		typedef std::map<std::string, unsigned int>::iterator LUTIterator; 
		
		/**
		 * \var lut_
		 * \brief maintains the associative array for the lookup table
		 */ 
		LUT lut_;
	}; // end class

} // end namespace
#endif


