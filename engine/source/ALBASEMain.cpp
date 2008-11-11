
// CODESTYLE: v2.0

// ALBASEMain.cpp
// Project: Allegro Base Project (ALBASE)
// Author: Richard Marks
// Purpose: An empty project for starting a game based on Allegro

// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "ALBASEMain.h"

// include the error reporting header
#include "DebugReport.h"

// include the game header
#include "Game.h"

// include the game state manager header
#include "GameStateManager.h"

namespace ALBASE
{
	ALBASEMain::ALBASEMain() :
		backBuffer_(0)
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	ALBASEMain::~ALBASEMain()
	{
		// implement class destructor here
		if (0 != backBuffer_)
		{
			destroy_bitmap(backBuffer_);
			backBuffer_ = 0;
		}
	} // end destructor
	
	/**************************************************************************/
	
	int ALBASEMain::Initialize(int argc, char* argv[])
	{
		// implement class initialization here
		LogMessage("\nCCPS Solutions Presents\n\n"
			"ALBASE v1.0 - An Allegro Game Framework\n"
			"Developed by Richard Marks\n");
			
		/**
		* Parse the optional command-line flags:
		*
		* 	specify -f or --fullscreen to lose the window and use the whole screen
		* 	specify -q or --quiet to lose audio support
		* 	specify -h or --help to view a list of available options
		*
		*/
		bool useFullscreen = false;
		bool useSound = true;
		if (argc > 1)
		{
			for (int index = 1; index < argc; index++)
			{
				if (!stricmp(argv[index], "-f") || !stricmp(argv[index], "--fullscreen"))
				{
					useFullscreen = true;
				}
				else if (!stricmp(argv[index], "-q") || !stricmp(argv[index], "--quiet"))
				{
					useSound = false;
				}
				else if(!stricmp(argv[index], "-h") || !stricmp(argv[index], "--help"))
				{
					fprintf(stderr, 
					"Usage: %s [-|--][f|h|q|fullscreen|quiet|help]\n\n"
					"\tspecify -f or --fullscreen to lose the window and use the whole screen\n"
					"\tspecify -q or --quiet to lose audio support\n"
					"\tspecify -h or --help to view this information.\n"
					"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n", 
					argv[0]);
					exit(1);
				}
			}
		}
		
		
		
		// initialize Allegro
		if (0 != allegro_init())
		{
			LogFatal("Could not initialize Allegro!");
		}

		// install the Allegro timer driver
		if (0 != install_timer())
		{
			LogFatal("Could not install Allegro Timer driver!");
		}
		
		// install the Allegro keyboard driver
		if (0 != install_keyboard())
		{
			LogFatal("Could not install Allegro Keyboard driver!");
		}
		
		// install the Allegro mouse driver
		if (install_mouse() < 0)
		{
			LogFatal("Could not install Allegro Mouse driver!");
		}
		
		// set the video mode
		set_color_depth(24);
		int displayMode = (useFullscreen) ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED;
		if (set_gfx_mode(displayMode, 640, 480, 0, 0) < 0)
		{
			LogFatal("Could not set the display mode to 640x480 at 24bpp!");
		}
		
		// create the backbuffer surface
		backBuffer_ = create_bitmap(SCREEN_W, SCREEN_H);
		if (0 == backBuffer_)
		{
			LogFatal("Could not create the backbuffer surface!");
		}
		
		// install the Allegro audio driver
		if (useSound)
		{
			if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) < 0)
			{
				LogFatal("Could not install the Allegro audio driver! Try using the --quiet command line flag.");
			}
		}
		
		GAME::GameInstance->SetRenderTarget(backBuffer_);
		GAME::GameInstance->Initialize();
		LogMessage("Initialization Complete.");
		
		return 0;
	} // end initialization
	
	/**************************************************************************/
	
	int ALBASEMain::Execute()
	{
		// implement class main loop here
		
		// if there are still states in the game state stack
		while(!ENGINE::GameStateManager->Empty())
		{
			// process the state
			ENGINE::GameStateManager->ExecuteNextState();
		}
		
		return 0;
	} // end main code
	
	/**************************************************************************/
	
	BITMAP* ALBASEMain::GetBackBuffer()
	{
		return backBuffer_;
	}
} // end namespace


