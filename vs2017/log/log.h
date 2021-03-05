#ifndef LOG_H_
#define LOG_H_
#define  LOG4CPLUS_STATIC
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/helpers/loglog.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>
#ifdef _WIN32
#include <log4cplus/win32debugappender.h>
#endif


#define LOG_SIZE	   30000
#define LOG_LEV_DEBUG	1
#define LOG_LEV_METHOD	2
#define LOG_LEV_WARN	3
#define LOG_LEV_ERROR	4
#define LOG_LEV_INFO	5
#define LOG_FILE  	   ("linkdood")

extern const  char*  filename;
extern int    line;

#ifdef _WIN32
	#define TAG_PREFFIX   ("pc-win-xp")
#elif defined (__linux__)
	#define TAG_PREFFIX   ("pc-linux-xp")
#elif defined (__APPLE__)
    #define TAG_PREFFIX   ("pc-mac-xp")
#endif

#ifdef _WIN32
	#define FILE_NAME(x) (strrchr(x,'\\')?(strrchr(x,'\\')+1):(x))
#else
	#define FILE_NAME(x) (strrchr(x,'/')?(strrchr(x,'/')+1):(x))
#endif

#ifdef UNICODE
//#define Log LogW
#else
#define BEGIN (filename=FILE_NAME(__FILE__),line=__LINE__,LogA(LOG_LEV_METHOD,LOG_FILE,"%s",__FUNCTION__))
#define END   (filename=FILE_NAME(__FILE__),line=__LINE__,LogA(LOG_LEV_METHOD,LOG_FILE,"%s",__FUNCTION__))
#ifdef _WIN32
	#define AddLog   filename=FILE_NAME(__FILE__),line=__LINE__,AddLogB 
	#define Log				  filename=FILE_NAME(__FILE__),line=__LINE__,LogA 
	#define ADD_TAG(funcname) (filename=FILE_NAME(__FILE__),line=__LINE__,LogA(LOG_LEV_INFO,LOG_FILE,"%s-%s",TAG_PREFFIX,funcname))
#else
	#define AddLog   filename=FILE_NAME(__FILE__),line=__LINE__,AddLogB 
	#define Log filename=__FILE__,line=__LINE__,LogA
	#define ADD_TAG(funcname) (filename=__FILE__,line=__LINE__,LogA(LOG_LEV_INFO,LOG_FILE,"%s-%s",TAG_PREFFIX,funcname))
#endif
#endif
inline void InitLogger(std::string logfilename)
{
	log4cplus::initialize();
	log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(true);
	try {
		
		log4cplus::SharedAppenderPtr append_file(new log4cplus::RollingFileAppender(LOG4CPLUS_TEXT(logfilename), 50*1024*1024));
		log4cplus::SharedAppenderPtr append_console(new log4cplus::ConsoleAppender());
		log4cplus::tstring pattern = LOG4CPLUS_TEXT("[%D{%H:%M:%S.%q} %p %l] %m%n");
#ifdef _WIN32
		log4cplus::SharedAppenderPtr append_win32(new log4cplus::Win32DebugAppender());
		append_win32->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));
		log4cplus::Logger::getRoot().addAppender(append_win32);
#endif
		append_console->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));
		append_file->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern)));
		log4cplus::Logger::getRoot().addAppender(append_console);
		log4cplus::Logger::getRoot().addAppender(append_file);
		log4cplus::Logger::getRoot().setLogLevel(log4cplus::ALL_LOG_LEVEL);
	}
	catch (...) {
		log4cplus::Logger::getRoot().log(log4cplus::FATAL_LOG_LEVEL, LOG4CPLUS_TEXT("Exception occured..."));
	}
}

inline void AddLogB(int level, const char* file, const char * format, ...)
{
	//filename=FILE_NAME(__FILE__),line=__LINE__;
	char	szLine[LOG_SIZE]	= {0};
	va_list	ap;

	va_start(ap, format);
#ifdef _WIN32
	_vsnprintf_s(szLine, LOG_SIZE, format, ap);
#else
	vsnprintf(szLine, LOG_SIZE, format, ap);
	printf("[pc]===%s===[pc]\n", szLine);
#endif
	va_end(ap);

	switch (level)
	{
	case LOG_LEV_DEBUG:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::DEBUG_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_WARN:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::WARN_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_ERROR:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::ERROR_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_INFO:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::INFO_LOG_LEVEL, szLine, filename, line);
			break;
		}
	}
}

inline void AddLogB(int level, const char * format, ...)
{
	//filename=FILE_NAME(__FILE__),line=__LINE__;
	const char* file = LOG_FILE;
	char	szLine[LOG_SIZE]	= {0};
	va_list	ap;

	va_start(ap, format);
#ifdef _WIN32
	_vsnprintf_s(szLine, LOG_SIZE, format, ap);
#else
	vsnprintf(szLine, LOG_SIZE, format, ap);
	printf("[pc]===%s===[pc]\n", szLine);
#endif
	va_end(ap);

	switch (level)
	{
	case LOG_LEV_DEBUG:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::DEBUG_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_WARN:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::WARN_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_ERROR:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::ERROR_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_INFO:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::INFO_LOG_LEVEL, szLine, filename, line);
			break;
		}
	}
}

inline void LogA(int level, const char* file, const char * format, ...)
{
	
	char	szLine[LOG_SIZE]	= {0};
	va_list	ap;
	
	va_start(ap, format);
#ifdef _WIN32
	_vsnprintf_s(szLine, LOG_SIZE, format, ap);
#else
	vsnprintf(szLine, LOG_SIZE, format, ap);
	printf("[pc]===%s===[pc]\n", szLine);
#endif
	va_end(ap);

	switch (level)
	{
	case LOG_LEV_DEBUG:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::DEBUG_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_WARN:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::WARN_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_ERROR:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::ERROR_LOG_LEVEL, szLine, filename, line);
			break;
		}
	case LOG_LEV_INFO:
		{
			log4cplus::Logger::getInstance(file).log(log4cplus::INFO_LOG_LEVEL, szLine, filename, line);
			break;
		}
	}
	
}
#ifdef _WIN32
	#define LOG_METHOD(msg,file)	log4cplus::TraceLogger _log4cplus_trace_logger(log4cplus::Logger::getInstance(file), msg, FILE_NAME(__FILE__), line)
#else
	#define LOG_METHOD(msg,file)	log4cplus::TraceLogger _log4cplus_trace_logger(log4cplus::Logger::getInstance(file), msg, __FILE__, line)
#endif

#endif

