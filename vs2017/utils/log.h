#ifndef LOG_H_
#define LOG_H_
#define  LOG4CPLUS_STATIC
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/loggingmacros.h>

#include <stdarg.h>
#include <string>


#define LOG_SIZE	10000

#define LOG_LEV_DEBUG	1
#define LOG_LEV_METHOD	2
#define LOG_LEV_WARN	3
#define LOG_LEV_ERROR	4

#define LOG_FILE_		"linkdood"

inline void InitLogger( __in std::string strProperties )
{
	log4cplus::PropertyConfigurator::doConfigure(strProperties);
}

void inline LogA( __in int level, __in const char* file, const char * format, ...)
{
	
	char	szLine[LOG_SIZE]	= {0};
	va_list	ap					= NULL;
	
	va_start(ap, format);
	_vsnprintf_s(szLine, LOG_SIZE, format, ap);
	va_end(ap);

	switch (level)
	{
	case LOG_LEV_DEBUG:
		{
			LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance(file), szLine);
			break;
		}
	case LOG_LEV_METHOD:
		{
			LOG4CPLUS_TRACE(log4cplus::Logger::getInstance(file), szLine);
			break;
		}
	case LOG_LEV_WARN:
		{
			LOG4CPLUS_WARN(log4cplus::Logger::getInstance(file), szLine);
			break;
		}
	case LOG_LEV_ERROR:
		{
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(file), szLine);
			break;
		}
	}
	
}

#ifdef UNICODE
//#define Log LogW
#else
#define Log LogA
#endif

#define LOG_DEBUG(msg) \
	LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance("log"), msg)
#define LOG_INFO(msg) \
	LOG4CPLUS_INFO(log4cplus::Logger::getInstance("log"), msg) 
#define LOG_WARN(msg) \
	LOG4CPLUS_WARN(log4cplus::Logger::getInstance("log"), msg)
#define LOG_ERROR(msg) \
	LOG4CPLUS_ERROR(log4cplus::Logger::getInstance("log"), msg)
#define LOG_METHOD(msg,file)	\
	LOG4CPLUS_TRACE_METHOD(log4cplus::Logger::getInstance(file), msg)

#endif
