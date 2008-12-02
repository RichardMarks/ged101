
// CODESTYLE: v2.0

// main.cpp
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks

/**
 * \file main.cpp
 * \brief Program Entry Point - Implementation
 */

// include the common headers
//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
//#include <cstdarg>

// include the error reporting header
//#include "DebugReport.h"

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
	if (MainSystem->Initialize(argc, argv))
	{
		return MainSystem->Execute();
	}
	
	return 1;
}


#if 0
ENGINE::MainSystem* runner = 0;

/**
 * Makes certain that the game engine gets shutdown properly when we use the exit function in our code.
 */
void PerformShutdownCleansing();

/**************************************************************************/

/**
 * Entry Point of any program that uses the ged101 engine.\n
 * You do not have to worry about writing a main() function
 * @param argc the number of parameters passed to the executable's name
 * @param argv the array of parameters passed to the executable's name
 */
int main(int argc, char* argv[])
{
	int result = 0;
	
	atexit(PerformShutdownCleansing);	
	
	runner = new ENGINE::MainSystem();
	
	if (0 == runner->Initialize(argc, argv))
	{
		result = runner->Execute();
	}
	
	return result;
}

/**************************************************************************/
	
void PerformShutdownCleansing()
{
	if (0 != runner)
	{
		delete runner;
		runner = 0;
		LogMessage("Proper shutdown of ged101 game engine complete.");
	}
}

#endif

