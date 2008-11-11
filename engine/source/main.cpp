
// CODESTYLE: v2.0

// main.cpp
// Project: Allegro Base Project (ALBASE)
// Author: Richard Marks

#include <cstdlib>
#include "ALBASEMain.h"

ALBASE::ALBASEMain* runner = 0;

void PerformShutdownCleansing();

/**************************************************************************/
	
int main(int argc, char* argv[])
{
	int result = 0;
	
	atexit(PerformShutdownCleansing);	
	
	runner = new ALBASE::ALBASEMain();
	
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
	}
}


