
// CODESTYLE: v2.0

// ALBASEMain.h
// Project: Allegro Base Project (ALBASE)
// Author: Richard Marks
// Purpose: An empty project for starting a game based on Allegro

#ifndef __ALBASEMAIN_H__
#define __ALBASEMAIN_H__

struct BITMAP;

namespace ALBASE
{
	class ALBASEMain
	{
	public:
		// public members should be declared here

		ALBASEMain();

		~ALBASEMain();

		int Initialize(int argc, char* argv[]);

		int Execute();
		
		BITMAP* GetBackBuffer();
	private:
		// private members should be declared here

		BITMAP* backBuffer_;
	}; // end class

} // end namespace
#endif


