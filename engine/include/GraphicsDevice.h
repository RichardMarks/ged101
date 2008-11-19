
// CODESTYLE: v2.0

// GraphicsDevice.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Interface to the physical graphics device; The screen.

#ifndef __GRAPHICSDEVICE_H__
#define __GRAPHICSDEVICE_H__

/**
 * \file GraphicsDevice.h
 * \brief Graphics Device Interface Module - Header
 */
 
namespace ENGINE
{
	// forward declare the classes we need to use
	class ImageResource;
	
	/**
	 * \enum GraphicsDeviceDisplayMode
	 * \brief Possible modes that the graphics device can be in are windowed or Fullscreen...there isn't much else!
	 */
	enum GraphicsDeviceDisplayMode
	{
		GraphicsDevice_Windowed,
		GraphicsDevice_Fullscreen
	};
	
	/**
	 * \enum GraphicsDeviceDisplayDepth
	 * \brief Possible color depths that the engine will support.
	 */
	enum GraphicsDeviceDisplayDepth
	{
		GraphicsDevice_8bit = 8,
		GraphicsDevice_16bit = 16,
		GraphicsDevice_24bit = 24,
		GraphicsDevice_32bit = 32
	};
	
	//! lowest X axis resolution that we will ever try to place the display into
	const int GRAPHICS_DEVICE_FALLBACK_DISPLAY_WIDTH = 640;
	
	//! lowest Y axis resolution that we will ever try to place the display into
	const int GRAPHICS_DEVICE_FALLBACK_DISPLAY_HEIGHT = 480;
	
	//! lowest color depth that we will ever try to place the display into
	const GraphicsDeviceDisplayDepth GRAPHICS_DEVICE_FALLBACK_DISPLAY_BPP = GraphicsDevice_8bit;
	
	/**
	 * \class GraphicsDeviceSingleton
	 * \brief Interface to the physical graphics device; The screen.
	 *
	 * This class is implemented as a Singleton class, since there should never
	 * be a need for multiple graphics devices. Multi-monitor support is not available
	 * in this engine.\n
	 * There is a MACRO defined called GraphicsDevice that is just an alias to calling the 
	 * GraphicsDeviceSingleton::GetInstance() function which returns a pointer to the singleton instance.
	 * There are several shortcut functions that give an easier to use interface such as
	 * the GraphicsDeviceSingleton::GetDisplayWidth() and GraphicsDeviceSingleton::GetDisplayHeight() 
	 * functions will handle obtaining the values from the ENGINE::ImageResource class for you.
	 * \n\n
	 * The first thing you should do is call the GraphicsDeviceSingleton::SetDisplayMode(),
	 * GraphicsDeviceSingleton::SetDisplayResolution(), GraphicsDeviceSingleton::SetDisplayColorDepth() functions
	 * to setup the graphics device. This needs to be done before you start drawing things.
	 * \n\n
	 * The general idea is that you use the GraphicsDeviceSingleton::BeginScene() function to clear the scene, and then 
	 * you call the GraphicsDeviceSingleton::GetSecondaryDisplayBuffer() function to get a pointer to the
	 * secondary display buffer, and you do all your drawing of your scene onto this, then you use the 
	 * GraphicsDeviceSingleton::EndScene() function to copy the contents of the scene to the visible screen so that your scene is shown to the user.
	 */
	class GraphicsDeviceSingleton
	{
	public:
	
		/**
		 * \return a pointer to the graphics device singleton class instance 
		 */
		static GraphicsDeviceSingleton* GetInstance();
		
		/**
		 * Fills the entire secondary display buffer with the specified color. Calling without any parameters will fill with BLACK. 
		 * @param color is the color to fill the image with. Get an int value for an RGB color using using Allegro's makecol(red,green,blue) function. The default is BLACK
		 */
		void BeginScene(int color = 0);
		
		/**
		 * Flips the secondary display buffer to the primary display buffer so that the user can see the scene.
		 */
		void EndScene();
		
		/**
		 * Attempts to set the display mode to either fullscreen or windowed modes.
		 * This function requires that the display resolution and color depth have already been set.
		 * @param mode can be GraphicsDevice_Windowed or GraphicsDevice_Fullscreen
		 * \return true on success, false on failure
		 */
		bool SetDisplayMode(GraphicsDeviceDisplayMode mode = GraphicsDevice_Windowed);
		
		/**
		 * Attempts to set the display resolution.
		 * This function requires that the display color depth have already been set.
		 * @param displayWidth is the width of the display resolution in pixels.
		 * @param displayHeight is the height of the display resolution in pixels.
		 * \return true on success, false on failure
		 */
		bool SetDisplayResolution(int displayWidth, int displayHeight);
		
		/**
		 * Attempts to set the display color depth.
		 * When called with no parameter, the default of 16 bits per pixel is used.
		 * @param bitsPerPixel is the color depth. Possible values are GraphicsDevice_8bit, GraphicsDevice_16bit, GraphicsDevice_24bit, and GraphicsDevice_32bit
		 * \return true on success, false on failure
		 */
		bool SetDisplayColorDepth(GraphicsDeviceDisplayDepth bitsPerPixel = GraphicsDevice_16bit);
		
		/**
		 * Attempts to setup the display resolution, color depth, and mode by calling the single \a SetDisplay functions.\n
		 * \sa GraphicsDeviceSingleton::SetDisplayResolution(), GraphicsDeviceSingleton::SetDisplayColorDepth(), GraphicsDeviceSingleton::SetDisplayMode()
		 * @param displayWidth is the width of the display resolution in pixels.
		 * @param displayHeight is the height of the display resolution in pixels.
		 * @param bitsPerPixel is the color depth. Possible values are GraphicsDevice_8bit, GraphicsDevice_16bit, GraphicsDevice_24bit, and GraphicsDevice_32bit
		 * @param mode can be GraphicsDevice_Windowed or GraphicsDevice_Fullscreen
		 * \return true on success, false on failure
		 */
		bool SetDisplay(
			int displayWidth, 
			int displayHeight, 
			GraphicsDeviceDisplayDepth bitsPerPixel, 
			GraphicsDeviceDisplayMode mode);
		
		/**
		 * Get the state of the display mode, its going to be either windowed, or fullscreen.
		 * \return the current value of GraphicsDeviceSingleton::displayMode_
		 */
		GraphicsDeviceDisplayMode GetDisplayMode();
		
		/**
		 * \return the display width in pixels
		 */
		int GetDisplayWidth();
		
		/**
		 * \return the display height in pixels
		 */
		int GetDisplayHeight();
		
		/**
		 * Get the color depth of the display
		 * \return the current value of GraphicsDeviceSingleton::displayBitsPerPixel_
		 */
		GraphicsDeviceDisplayDepth GetDisplayBitsPerPixel();
		
		/**
		 * Get a pointer to the primary display buffer
		 * \return GraphicsDeviceSingleton::primaryDisplayBuffer_ or 0 if the display has not been setup
		 */
		ImageResource* GetPrimaryDisplayBuffer();
		
		/**
		 * Get a pointer to the secondary display buffer
		 * \return GraphicsDeviceSingleton::secondaryDisplayBuffer_ or 0 if the display has not been setup
		 */
		ImageResource* GetSecondaryDisplayBuffer();
		
		/**
		 * makes a call to the GraphicsDeviceSingleton::Destroy() function to de-allocate the allocated memory
		 */
		~GraphicsDeviceSingleton();
		
	private:
		/**
		 * De-allocates any allocated memory
		 */
		void Destroy();
		
		/**
		 * constructor is hidden because this is a singleton class
		 */
		GraphicsDeviceSingleton();
		
		/**
		 * copy constructor is hidden because this class cannot be copied
		 */
		GraphicsDeviceSingleton(const GraphicsDeviceSingleton& rhs);
		
		/**
		 * assignment operator is hidden because you cannot copy this class
		 */
		const GraphicsDeviceSingleton& operator=(const GraphicsDeviceSingleton& rhs);
		
		/**
		 * \var primaryDisplayBuffer_
		 * \brief a pointer to an ImageResource that serves as the physical screen buffer
		 */
		ImageResource* primaryDisplayBuffer_;
		
		/**
		 * \var secondaryDisplayBuffer_
		 * \brief a pointer to an ImageResource that serves as the back-buffer that all drawing should be done on
		 */
		ImageResource* secondaryDisplayBuffer_;
		
		/**
		 * \var displayMode_
		 * \brief the current state of the display mode. Windowed or Fullscreen.
		 */
		GraphicsDeviceDisplayMode displayMode_;
		
		/**
		 * \var displayWidth_
		 * \brief the display resolution width in pixels
		 */
		int displayWidth_;
		
		/**
		 * \var displayHeight_
		 * \brief the display resolution height in pixels
		 */
		int displayHeight_;
		
		/**
		 * \var displayBitsPerPixel_
		 * \brief the color depth of the display
		 */
		GraphicsDeviceDisplayDepth displayBitsPerPixel_;
	}; // end class

/**
 * \def GraphicsDevice
 * \brief an alias for the GraphicsDeviceSingleton::GetInstance() function to make your code clean.
 */
#define GraphicsDevice GraphicsDeviceSingleton::GetInstance()
} // end namespace
#endif


