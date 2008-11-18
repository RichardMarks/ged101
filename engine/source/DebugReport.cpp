
// CODESTYLE: v2.0

// DebugReport.cpp
// Project: Project Debugging Utility Library (DEBUG)
// Author: Richard Marks, RedSlash
// Purpose: debug support library

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <ctime>

#include "DebugReport.h"

namespace DEBUG
{
	DebugReportInfo::DebugReportInfo(const char* func, const char* file, int line) : 
		func_(func), 
		file_(file), 
		line_(line)
	{
	}
	
	/**************************************************************************/
	
	void DebugReportInfo::PrintLog(unsigned int severity, const char* message, va_list va)
	{
		char logBuffer[DEBUG::DBGREP_MAX_REPORT_LENGTH];

		snprintf(logBuffer,DEBUG::DBGREP_MAX_REPORT_LENGTH,
			"      Function: %s\n\t"
			"          Line: %d\n\t"
			"Report Details:\n\n\t\t",
			func_,
			line_);
		const int lengthReport = strlen(logBuffer);
		// concatenate printf-style message string to logBuffer for remaining buffer space minus two for the trailing \n and \0 characters
		vsnprintf(logBuffer + lengthReport, DEBUG::DBGREP_MAX_REPORT_LENGTH - lengthReport - 2, message, va);
		strncat(logBuffer, "\n", 2);
		DEBUG::DebugReport::Log(severity, file_, logBuffer);
	}

	/**************************************************************************/
	
	void DebugReportInfo::PrintWarning(const char* message, ...)
	{
		va_list va;
		va_start(va, message);
		PrintLog(DBGREP_WARNING, message, va);
		va_end(va);
	}
	
	/**************************************************************************/
	
	void DebugReportInfo::PrintError(const char* message, ...)
	{
		va_list va;
		va_start(va, message);
		PrintLog(DBGREP_ERROR, message, va);
		va_end(va);
	}
	
	/**************************************************************************/
	
	void DebugReportInfo::PrintFatal(const char* message, ...)
	{
		va_list va;
		va_start(va, message);
		PrintLog(DBGREP_FATAL, message, va);
		va_end(va);
	}
		
	/**************************************************************************/
	
	void DebugReportInfo::PrintMessage(const char* message, ...)
	{
		va_list va;
		va_start(va, message);
		PrintLog(DBGREP_MESSAGE, message, va);
		va_end(va);
	}
	
	/**************************************************************************/
	
	/**
	* The Log method handles error reporting in a clean easy to use fashion.
	* It is not recommended to use this method directly, but to make use of the
	* supporting MACROs LogFatal, LogError, LogWarning, LogMessage
	*/
	void DebugReport::Log(unsigned int severity, const char* location, const char* message)
	{
		FILE* fp = 0;
		
		// create a timestamp for the report
		char timeStampBuffer[128];
		time_t rawTime;
		time(&rawTime);
		strftime (timeStampBuffer, 128, "%I:%M:%S %p %Z on %m-%d-%Y", localtime(&rawTime));
		
		// how severe is the reporting?
		switch(severity)
		{
			// this is a fatal error. process execution will cease after this call
			case DBGREP_FATAL:
			{
				fp = fopen("errors.txt", "a");
				if (fp)
				{
					fprintf(fp, 
						"********************************************************************************\n"
						"A Fatal Error has occurred at %s in the file: %s\n\t"
						"%s\n"
						"********************************************************************************\n\n", 
						timeStampBuffer, location, message);
					fclose(fp);
				}
				fprintf(stderr, "A Fatal Error has occurred at %s in the file: %s\n\t%s\n\n", timeStampBuffer, location, message);
				exit(1);
			} break;
			
			// just an error. it is logged and process execution continues.
			case DBGREP_ERROR:
			{
				fp = fopen("errors.txt", "a");
				if (fp)
				{
					fprintf(fp, 
						"********************************************************************************\n"
						"An Error has occurred at %s in the file: %s\n\t"
						"%s\n"
						"********************************************************************************\n\n", 
						timeStampBuffer, location, message);
					fclose(fp);
				}
				fprintf(stderr, "An Error has occurred at %s in the file: %s\n\t%s\n\n", timeStampBuffer, location, message);
			} break;
			
			// a warning. it is logged and process execution continues.
			case DBGREP_WARNING:
			{
				// open warnings.txt and write the message to it
				fp = fopen("warnings.txt", "a");
				if (fp)
				{
					fprintf(fp, 
						"********************************************************************************\n"
						"A Warning has occurred at %s in the file: %s\n\t"
						"%s\n"
						"********************************************************************************\n\n", 
						timeStampBuffer, location, message);
					fclose(fp);
				}
				fprintf(stderr, "A Warning has occurred at %s in the file: %s\n\t%s\n\n", timeStampBuffer, location, message);
			} break;
			
			// a message. it is logged and process execution continues.
			case DBGREP_MESSAGE:
			{
				// open messages.txt and write the message to it
				fp = fopen("messages.txt", "a");
				if (fp)
				{
					fprintf(fp, 
						"********************************************************************************\n"
						"A Message Reported at %s from the file: %s\n\t"
						"%s\n"
						"********************************************************************************\n\n", 
						timeStampBuffer, location, message);
					fclose(fp);
				}
				fprintf(stderr, "A Message Reported at %s from the file: %s\n\t%s\n", timeStampBuffer, location, message);
			} break;
			
			default: break;
		}
	}
	
} // end namespace


