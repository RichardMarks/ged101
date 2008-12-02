
// CODESTYLE: v2.0

// main.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks

/**
 * \file main.cpp
 * \brief Program Entry Point - Implementation
 */

// include the Allegro header
#include <allegro.h>

// include the engine main system header
#include "MainSystem.h"

using namespace ENGINE;

/**
 * Entry Point of any program that uses the ged101 engine.\n
 * You do not have to worry about writing a main() function
 * @param argc the number of parameters passed to the executable's name
 * @param argv the array of parameters passed to the executable's name
 */
int main(int argc, char* argv[])
{
	if (0 == MainSystem->Initialize(argc, argv))
	{
		return MainSystem->Execute();
	}
	
	return 1;
}
END_OF_MAIN();
