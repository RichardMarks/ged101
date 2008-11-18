
// CODESTYLE: v2.0

// DebugReport.h
// Project: Project Debugging Utility Library (DEBUG)
// Author: Richard Marks, RedSlash
// Purpose: debug support library

#ifndef __DEBUGREPORT_H__
#define __DEBUGREPORT_H__

#include <cstdarg>

/**
 * \file DebugReport.h
 * \brief Project Debugging Utility Library - Error Reporting Header
 *
 * The Project Debugging Utility Library is comprised of a few classes that make
 * error reporting an easy task. There are several levels of reporting severity.\n
 * Including
 * \li Fatal Errors
 * \li Non-fatal Error
 * \li Warnings
 * \li Generic Messages
 * \sa DBGREP_FATAL, DBGREP_ERROR, DBGREP_WARNING, DBGREP_MESSAGE
 * \n\n
 * The use of the classes should be restricted to using only the MACROs in your code.
 * \sa LogFatal, LogError, LogWarning, LogMessage
 */

// __PRETTY_FUNCTION__ is a GNU extension, disable it if not GNU g++
#ifndef __GNUC__
#define __PRETTY_FUNCTION__ "This feature is unavailable on this compiler."
#endif

namespace DEBUG
{
	//! writes an error to errors.txt and exits the game
	const unsigned int DBGREP_FATAL 			= 0xAA;
	
	//! writes an error to errors.txt
	const unsigned int DBGREP_ERROR 			= 0xBB;
	
	//! writes a warning to warnings.txt
	const unsigned int DBGREP_WARNING 			= 0xCC;
	
	//! writes a message to messages.txt
	const unsigned int DBGREP_MESSAGE 			= 0xDD;
	
	//! 4096 characters max report length   
	const unsigned int DBGREP_MAX_REPORT_LENGTH = 0x1000; 
	
	/**
	 * \class DebugReportInfo
	 * \brief The DebugReportInfo class is a helper class that gives the functionality of a printf-style error reporting function. 
	 * The class stores the function, file and line information so that it may be used later when calling the real 
	 * reporting functions from the DebugReport class.\n
	 * Many thanks to RedSlash for this contribution.
	 */
	class DebugReportInfo
	{
	public:
		/**
		 * Initializes class with function, file and line information.
		 * @param func is the name of the Function that the report is being made from. Usually you should pass __PRETTY_FUNCTION__ here, or __func__.
		 * @param file is the name of the File that the report is being made in. Usually __FILE__ should be used here.
		 * @param line is the line number that the report is being made on. This is almost always __LINE__.
		 */
		DebugReportInfo(const char* func, const char* file, int line);
		
		/**
		 * Formats a report based on the information provided and makes a call to the DebugReport::Log() function.
		 * @param severity is the report severity level. This can be any of the values DBGREP_WARNING, DBGREP_FATAL, DBGREP_ERROR or DBGREP_MESSAGE.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 * @param va is an optional number of arguments may be passed here to satisfy the previous printf-style C-string.
		 */ 
		void PrintLog(unsigned int severity, const char* message, va_list va);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DBGREP_WARNING severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintWarning(const char* message, ...);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DBGREP_ERROR severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintError(const char* message, ...);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DBGREP_FATAL severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintFatal(const char* message, ...);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DBGREP_MESSAGE severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintMessage(const char* message, ...);
		
	private:
		//! The name of the Function that the report is being made from. Usually the value of __PRETTY_FUNCTION__ or __func__.
		const char* func_;
		
		//! The name of the File that the report is being made in. Usually the value of __FILE__.
		const char* file_;
		
		//! The line number that the report is being made on. This is almost always __LINE__.
		int line_; 			
	}; // end class
	
	/**
	 * \class DebugReport
	 * \brief Handles the actual report logging functionality of the debug system.
	 * The DebugReport class only exposes the static DebugReport::Log() function.
	 * Instances of the DebugReport class cannot be made.
	 * Example use: DebugReport::Log(DBGREP_FATAL, "Engine::Initialize()", "Could not Initialize the Engine!");
	 */
	class DebugReport
	{
	public:
		/**
		 * The DebugReport::Log function writes reports to errors.txt warnings.txt or messages.txt based on the report severity level.
		 * It is not recommended to use this function directly, but to make use of the
		 * supporting MACROs: LogFatal, LogError, LogWarning, LogMessage
		 * @param severity is the report severity level. This can be any of the values DBGREP_WARNING, DBGREP_FATAL, DBGREP_ERROR or DBGREP_MESSAGE.
		 * @param location is the name of the File that the report is being made in. Usually the value of __FILE__.
		 * @param message is the message to be reported. This should have been created using the functions in the DebugReportInfo class.
		 */
		static void Log(
			unsigned int severity = DBGREP_WARNING,
			const char* location = "",
			const char* message = "");

	private:
		DebugReport()
		{
			 //! We NEVER need to create an instance of this class.
		};
	}; // end class

	/**
	 * \def LogFatal
	 * \brief reports a fatal error and kills the running process
	 * \def LogError
	 * \brief reports an error and continues running
	 * \def LogWarning
	 * \brief reports a warning and continues running
	 * \def LogMessage
	 * \brief reports a message and continues running
	 */

	#define LogFatal DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintFatal
	#define LogError DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintError
	#define LogWarning DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintWarning
	#define LogMessage DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintMessage
	
} // end namespace
#endif


