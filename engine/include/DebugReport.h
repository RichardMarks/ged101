
// CODESTYLE: v2.0

// DebugReport.h
// Project: Project Debugging Utility Library (DEBUG)
// Author: Richard Marks, RedSlash
// Purpose: debug support library

#ifndef __DEBUGREPORT_H__
#define __DEBUGREPORT_H__

#include <cstdarg>

// __PRETTY_FUNCTION__ is a GNU extension, disable it if not GNU g++
#ifndef __GNUC__
#define __PRETTY_FUNCTION__ "n/a"
#endif

namespace DEBUG
{
	/** 
	* Reporting Severity Levels
	*/
	const unsigned int DBGREP_FATAL 			= 0xAA;   /// writes an error to errors.txt and exits the game
	const unsigned int DBGREP_ERROR 			= 0xBB;   /// writes an error to errors.txt
	const unsigned int DBGREP_WARNING 			= 0xCC;   /// writes a warning to warnings.txt
	const unsigned int DBGREP_MESSAGE 			= 0xDD;   /// writes a message to messages.txt
	const unsigned int DBGREP_MAX_REPORT_LENGTH = 0x1000; /// 4096 characters max report length
	
	/**
	* Helper class for generating reports with file and line info.
	* Thanks RedSlash
	*/
	class DebugReportInfo
	{
	public:
		/**
		 * Initializes DebugLogger with file and line information.
		 * @param func Function name (usually pass __PRETTY_FUNCTION__ here, or __func__)
		 * @param file Filename (__FILE__)
		 * @param line Line number (__LINE__)
		 */
		DebugReportInfo(const char* func, const char* file, int line);
		
		/**
		 * Formats an error report based on the information provided and 
		 * calls DebugReport::Log().
		 * @param severity DBGREP_WARNING, DBGREP_FATAL or DBGREP_ERROR, DBGREP_MESSAGE
		 * @param message A printf-style message string.
		 * @param va A va_list.
		 */ 
		void PrintLog(unsigned int severity, const char* message, va_list va);
		
		/**
		 * Calls DebugReportInfo::PrintLog(DBGREP_WARNING,message,...).
		 * @param message A printf-style message string.
		 */
		void PrintWarning(const char* message, ...);
		
		/**
		 * Calls DebugReportInfo::PrintLog(DBGREP_ERROR,message,...).
		 * @param message A printf-style message string.
		 */
		void PrintError(const char* message, ...);
		
		/**
		 * Calls DebugReportInfo::PrintLog(DBGREP_FATAL,message,...).
		 * @param message A printf-style message string.
		 */
		void PrintFatal(const char* message, ...);
		
		/**
		 * Calls DebugReportInfo::PrintLog(DBGREP_MESSAGE,message,...).
		 * @param message A printf-style message string.
		 */
		void PrintMessage(const char* message, ...);
		
	private:
		const char* func_; 	/// holds the function information stored in __func__ or __PRETTY_FUNCTION__
		const char* file_; 	/// holds the file information stored in __FILE__
		int line_; 			/// holds the line number information stored in __LINE__
	}; // end class
	
	/**
	*	DebugReport only exposes the static Log method.
	*	Instances of the DebugReport class cannot be made.
	*	Example use: DebugReport::Log(DBGREP_FATAL, "Engine::Initialize()", "Could not Initialize the Engine!");
	*/
	class DebugReport
	{
	public:
		// public members should be declared here
		
		/**
		* The Log method handles error reporting in a clean easy to use fashion.
		* It is not recommended to use this method directly, but to make use of the
		* supporting MACROs LogFatal, LogError, LogWarning, LogMessage
		* @param severity DBGREP_WARNING, DBGREP_FATAL or DBGREP_ERROR, DBGREP_MESSAGE
		* @param location string holding file information
		* @param message string to be reported
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
	* Reporting MACROs
	* LogFatal		- reports a fatal error and kills the running process
	* LogError		- reports an error and continues running
	* LogWarning	- reports a warning and continues running
	* LogMessage	- reports a message and continues running
	*
	*/
	#define LogFatal DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintFatal
	#define LogError DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintError
	#define LogWarning DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintWarning
	#define LogMessage DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintMessage
	
#if 0
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
#endif

} // end namespace
#endif


