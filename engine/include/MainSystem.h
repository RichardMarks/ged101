
// CODESTYLE: v2.0

// MainSystem.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks
// Purpose: Initialization class for the ged101 engine

/**
 * \file MainSystem.h
 * \brief Main ged101 Engine Module - Header
 */

#ifndef __MAINSYSTEM_H__
#define __MAINSYSTEM_H__

namespace ENGINE
{
	/**
	 * \class MainSystemSingleton
	 * \brief Initialization class for the ged101 engine
	 */
	class MainSystemSingleton
	{
	public:
		/**
		 * \return a pointer to the class singleton
		 */
		static MainSystemSingleton* GetInstance();
		
		/**
		 * De-allocate any allocated memory
		 */
		~MainSystemSingleton();

		/**
		 * Initialize the ged101 engine
		 * @param argc is the number of parameters passed in \a argv
		 * @param argv is the array of parameters passed to the game's executable
		 */
		int Initialize(int argc, char* argv[]);

		/**
		 * Process the main execution loop
		 *
		 */
		int Execute();
		
	private:
		/**
		 * hidden constructor
		 */
		MainSystemSingleton();
		
		/**
		 * hidden copy constructor
		 */
		MainSystemSingleton(const MainSystemSingleton& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const MainSystemSingleton& operator=(const MainSystemSingleton& rhs);
		
	}; // end class

/**
 * \def MainSystem
 * \brief An alias for MainSystemSingleton::GetInstance()
 */
#define MainSystem MainSystemSingleton::GetInstance()
} // end namespace
#endif


