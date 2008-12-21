
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
 * \author Richard Marks <ccpsceo@gmail.com>, Redslash
 *
 * The Project Debugging Utility Library is comprised of a few classes that make
 * error reporting an easy task. There are several levels of reporting severity.\n
 * Including
 * \li Fatal Errors - errors are logged to a file, and the program exits to the OS.
 * \li Non-fatal Error - errors are logged to a file, and the program tries to continue.
 * \li Warnings - warnings are logged to a file, and the program continues.
 * \li Generic Messages - messages are logged to a file, and the program continues.
 * \sa DEBUG::DebugReport_Fatal, DEBUG::DebugReport_Error, DEBUG::DebugReport_Warning, DEBUG::DebugReport_Message
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
	/**
	 * \enum ReportSeverityLevel
	 * \brief Possible levels of severity for error reporting
	 */
	enum ReportSeverityLevel
	{
		//! writes an error to errors.txt and exits the game
		DebugReport_Fatal,
		//! writes an error to errors.txt
		DebugReport_Error,
		//! writes a warning to warnings.txt
		DebugReport_Warning,
		//! writes a message to messages.txt
		DebugReport_Message,
		//! just writes a message to log.txt with no line file info or anything
		DebugReport_SimpleMessage,
	};
	
	//! the maximum report length is limited to 4096 characters
	const unsigned int DBGREP_MAX_REPORT_LENGTH = 0x1000; 
	
	/**
	 * \class DebugReportInfo
	 * \brief A helper class that gives the functionality of a printf-style error reporting function. 
	 * \ingroup DebugGroup
	 * \author Richard Marks <ccpsceo@gmail.com>, Redslash
	 *
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
		 * @param severity is the report severity level. This can be any of the values DEBUG::DebugReport_Warning, DEBUG::DebugReport_Fatal, DEBUG::DebugReport_Error or DEBUG::DebugReport_Message.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 * @param va is an optional number of arguments may be passed here to satisfy the previous printf-style C-string.
		 */ 
		void PrintLog(ReportSeverityLevel severity, const char* message, va_list va);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DEBUG::DebugReport_Warning severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintWarning(const char* message, ...);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DEBUG::DebugReport_Error severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintError(const char* message, ...);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DEBUG::DebugReport_Fatal severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintFatal(const char* message, ...);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DEBUG::DebugReport_Message severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintMessage(const char* message, ...);
		
		/**
		 * Makes a call to the DebugReportInfo::PrintLog() function with the DEBUG::DebugReport_SimpleMessage severity level.
		 * @param message is the message to be reported. This is a printf-style C-string.
		 */
		void PrintSimpleMessage(const char* message, ...);
		
	private:
		/**
		 * hidden copy constructor
		 */
		DebugReportInfo(const DebugReportInfo& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const DebugReportInfo& operator=(const DebugReportInfo& rhs);
		
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
	 * \ingroup DebugGroup
	 * \author Richard Marks <ccpsceo@gmail.com>
	 *
	 * The DebugReport class only exposes the static DebugReport::Log() function.
	 * Instances of the DebugReport class cannot be made.
	 * Example use: DebugReport::Log(DEBUG::DebugReport_Fatal, "Engine::Initialize()", "Could not Initialize the Engine!");
	 */
	class DebugReport
	{
	public:
		/**
		 * The DebugReport::Log function writes reports to errors.txt warnings.txt or messages.txt based on the report severity level.
		 * It is not recommended to use this function directly, but to make use of the
		 * supporting MACROs: LogFatal, LogError, LogWarning, LogMessage
		 * @param severity is the report severity level. This can be any of the values DEBUG::DebugReport_Warning, DEBUG::DebugReport_Fatal, DEBUG::DebugReport_Error or DEBUG::DebugReport_Message.
		 * @param location is the name of the File that the report is being made in. Usually the value of __FILE__.
		 * @param message is the message to be reported. This should have been created using the functions in the DebugReportInfo class.
		 */
		static void Log(
			ReportSeverityLevel severity = DebugReport_Warning,
			const char* location = "",
			const char* message = "");

	private:
		/**
		 * hidden constructor
		 */
		DebugReport();
		
		/**
		 * hidden copy constructor
		 */
		DebugReport(const DebugReport& rhs);
		
		/**
		 * hidden assignment operator
		 */
		const DebugReport& operator=(const DebugReport& rhs);
		
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
	 * \def LogSimpleMessage
	 * \brief reports a message with no extra information attached and continues running
	 */

	#define LogFatal DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintFatal
	#define LogError DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintError
	#define LogWarning DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintWarning
	#define LogMessage DEBUG::DebugReportInfo(__PRETTY_FUNCTION__, __FILE__, __LINE__).PrintMessage
	#define LogSimpleMessage DEBUG::DebugReportInfo("simple", "", 1984).PrintSimpleMessage
	
} // end namespace
#endif


