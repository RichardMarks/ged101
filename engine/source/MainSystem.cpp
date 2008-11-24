
// CODESTYLE: v2.0

// MainSystem.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Initialization class for the ged101 engine

/**
 * \file MainSystem.cpp
 * \brief Main ged101 Engine Module - Implementation
 */
 
// include the common headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// include Allegro
#include <allegro.h>

// include the complementing header
#include "MainSystem.h"

// include the engine header
#include "Engine.h"

// include the game header
#include "Game.h"

namespace ENGINE
{
	MainSystemSingleton* MainSystemSingleton::GetInstance()
	{
		static MainSystemSingleton instance;
		return &instance;
	}
	
	/**************************************************************************/
	
	MainSystemSingleton::MainSystemSingleton()
	{
		// implement class constructor here
	} // end constructor
	
	/**************************************************************************/
	
	MainSystemSingleton::~MainSystemSingleton()
	{
		// implement class destructor here
	} // end destructor
	
	/**************************************************************************/
	
	int MainSystemSingleton::Initialize(int argc, char* argv[])
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
		
		// setup the graphics device
		GraphicsDevice->SetDisplay(
			640, 
			480, 
			GraphicsDevice_24bit, 
			(useFullscreen) ? GraphicsDevice_Fullscreen : GraphicsDevice_Windowed);
		
		// setup the audio device
		if (useSound)
		{
			AudioDevice->Initialize();
		}
		
		// setup the input device
		InputDevice->Initialize(INIT_ALLDEVICES);
		
		// call the game setup functions
		GAME::GameInstance->Initialize();
		LogMessage("Initialization Complete.");
		
		return 0;
	}
	
	/**************************************************************************/
	
	int MainSystemSingleton::Execute()
	{
		// implement class main loop here
		
		// if there are still states in the game state stack
		while(!GameStateManager->Empty())
		{
			// process the state
			GameStateManager->ExecuteNextState();
		}
		
		return 0;
	}
	
} // end namespace


