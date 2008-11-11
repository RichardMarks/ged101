
// CODESTYLE: v2.0

// DebugReport.h
// Project: Project Debugging Utility Library (DEBUG)
// Author: Richard Marks
// Purpose: debug support library

#ifndef __DEBUGREPORT_H__
#define __DEBUGREPORT_H__

namespace DEBUG
{
	/**
	*	DebugReport only exposes the static Log method.
	*	Instances of the DebugReport class cannot be made.
	*	Example use: DebugReport::Log(DBGREP_FATAL, "Engine::Initialize()", "Could not Initialize the Engine!");
	*
	* Reporting Severity Levels
	* DBGREP_FATAL 		- writes an error to errors.txt and exits the game
	* DBGREP_ERROR 		- writes an error to errors.txt
	* DBGREP_WARNING 	- writes a warning to warnings.txt
	* DBGREP_MESSAGE	- writes a message to messages.txt
	*/
	const unsigned int DBGREP_FATAL = 0xAA;
	const unsigned int DBGREP_ERROR = 0xBB;
	const unsigned int DBGREP_WARNING = 0xCC;
	const unsigned int DBGREP_MESSAGE = 0xDD;
	const unsigned int DBGREP_MAX_REPORT_LENGTH = 0x1000; // 4096 characters max report length
	
	class DebugReport
	{
	public:
		// public members should be declared here
		
		/**
		* The Log method handles error reporting in a clean easy to use fashion.
		* It is not recommended to use this method directly, but to make use of the
		* supporting MACROs LogFatal, LogError, LogWarning
		*/
		static void Log(
			unsigned int severity = DBGREP_WARNING,
			const char* location = "",
			const char* message = "");

	private:
		// private members should be declared here
		DebugReport(){}; // we never need to create an instance of this class
	}; // end class

	/**
	* The LogFatal MACRO takes a single string as a parameter and creates the code
	* to easily make a call to the log reporting method in the DebugReport class.
	* The code trys as best as possible to prevent errors from occurring, but you should
	* not pass anything other than a string to the macro.
	*
	* The execution of the running process is halted when this macro is used by calling exit(1);
	* The fatal error is logged to the errors.txt file
	*/
	#define LogFatal(message) do \
	{ \
		char logFatalBuffer[DEBUG::DBGREP_MAX_REPORT_LENGTH]; \
		sprintf(logFatalBuffer, \
			"      Function: %s\n\t" \
			"          Line: %d\n\t" \
			"Report Details:\n\n\t\t%s\n", \
			__PRETTY_FUNCTION__, \
			__LINE__, \
			static_cast<const char*>(message)); \
		DEBUG::DebugReport::Log(DEBUG::DBGREP_FATAL, __FILE__, logFatalBuffer); \
	} while(0)
	// END OF MACRO
	
	/**
	* The LogError MACRO takes a single string as a parameter and creates the code
	* to easily make a call to the log reporting method in the DebugReport class.
	* The code trys as best as possible to prevent errors from occurring, but you should
	* not pass anything other than a string to the macro.
	*
	* The error is logged to the errors.txt file
	*/
	#define LogError(message) do \
	{ \
		char logErrorBuffer[DEBUG::DBGREP_MAX_REPORT_LENGTH]; \
		sprintf(logErrorBuffer, \
			"      Function: %s\n\t" \
			"          Line: %d\n\t" \
			"Report Details:\n\n\t\t%s\n", \
			__PRETTY_FUNCTION__, \
			__LINE__, \
			static_cast<const char*>(message)); \
		DEBUG::DebugReport::Log(DEBUG::DBGREP_ERROR, __FILE__, logErrorBuffer); \
	} while(0)
	// END OF MACRO
	
	/**
	* The LogWarning MACRO takes a single string as a parameter and creates the code
	* to easily make a call to the log reporting method in the DebugReport class.
	* The code trys as best as possible to prevent errors from occurring, but you should
	* not pass anything other than a string to the macro.
	*
	* The warning is logged to the warnings.txt file
	*/
	#define LogWarning(message) do \
	{ \
		char logWarningBuffer[DEBUG::DBGREP_MAX_REPORT_LENGTH]; \
		sprintf(logWarningBuffer, \
			"      Function: %s\n\t" \
			"          Line: %d\n\t" \
			"Report Details:\n\n\t\t%s\n", \
			__PRETTY_FUNCTION__, \
			__LINE__, \
			static_cast<const char*>(message)); \
		DEBUG::DebugReport::Log(DEBUG::DBGREP_WARNING, __FILE__, logWarningBuffer); \
	} while(0)
	// END OF MACRO
	
	/**
	* The LogMessage MACRO takes a single string as a parameter and creates the code
	* to easily make a call to the log reporting method in the DebugReport class.
	* The code trys as best as possible to prevent errors from occurring, but you should
	* not pass anything other than a string to the macro.
	*
	* The message is logged to the messages.txt file
	*/
	#define LogMessage(message) do \
	{ \
		char logMessageBuffer[DEBUG::DBGREP_MAX_REPORT_LENGTH]; \
		sprintf(logMessageBuffer, \
			"      Function: %s\n\t" \
			"          Line: %d\n\t" \
			"Report Details:\n\n\t\t%s\n", \
			__PRETTY_FUNCTION__, \
			__LINE__, \
			static_cast<const char*>(message)); \
		DEBUG::DebugReport::Log(DEBUG::DBGREP_MESSAGE, __FILE__, logMessageBuffer); \
	} while(0)
	// END OF MACRO
	
} // end namespace
#endif


