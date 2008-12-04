
// CODESTYLE: v2.0

// ColorRGB.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: A class for creating 24-bit colors from red, green, and blue values.

/**
 * \file ColorRGB.h
 * \brief 24-bit Color Type - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */
 
#ifndef __COLORRGB_H__
#define __COLORRGB_H__

namespace ENGINE
{
	/**
	 * \class ColorRGB
	 * \brief A class for creating 24-bit colors from red, green, and blue values.
	 * \ingroup GraphicsGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 */
	class ColorRGB
	{
	public:
	
		/**
		 * default constructor
		 */
		ColorRGB();
		
		/**
		 * alternate constructor - creates a color from r,g,b values
		 * @param red is the value for the red intensity. expected 0 to 255
		 * @param green is the value for the green intensity. expected 0 to 255
		 * @param blue is the value for the blue intensity. expected 0 to 255
		 */
		ColorRGB(int red, int green, int blue);
		
		/**
		 * alternate constructor - creates a color from an HTML style 7-character C-string
		 * @param htmlColor is a 7-character C-string in the format "#RRGGBB" where R,G,B are HEX values from 00 to FF
		 */
		ColorRGB(const char* htmlColor);
		
		/**
		 * deconstructor
		 */
		~ColorRGB();
		
		/**
		 * Sets the RGB values of the color
		 * @param red is the value for the red intensity. expected 0 to 255
		 * @param green is the value for the green intensity. expected 0 to 255
		 * @param blue is the value for the blue intensity. expected 0 to 255
		 */
		void Set(int red, int green, int blue);
		
		/**
		 * Sets the R value of the color
		 * @param red is the value for the red intensity. expected 0 to 255
		 */
		void SetRed(int red);
		
		/**
		 * Sets the G value of the color
		 * @param green is the value for the green intensity. expected 0 to 255
		 */
		void SetGreen(int green);
		
		/**
		 * Sets the B value of the color
		 * @param blue is the value for the blue intensity. expected 0 to 255
		 */
		void SetBlue(int blue);
		
		/**
		 * Gets the color
		 * \return the color as an integer that Allegro's makecol() function returns 
		 */
		int Get();
		
		/**
		 * Gets the R value
		 * \return the value of the red intensity of the color
		 */
		int GetRed();
		
		/**
		 * Gets the G value
		 * \return the value of the green intensity of the color
		 */
		int GetGreen();
		
		/**
		 * Gets the B value
		 * \return the value of the blue intensity of the color
		 */
		int GetBlue();
		
	private:
	
		/**
		 * hidden copy constructor
		 */
		ColorRGB(const ColorRGB& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const ColorRGB& operator=(const ColorRGB& rhs);
		
		/**
		 * \var red_
		 * \brief red intensity of the color
		 */
		int red_;
		
		/**
		 * \var green_
		 * \brief green intensity of the color
		 */
		int green_;
		
		/**
		 * \var blue_
		 * \brief blue intensity of the color
		 */
		int blue_;	
	}; // end class

} // end namespace
#endif


