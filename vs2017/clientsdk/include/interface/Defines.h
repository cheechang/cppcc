#pragma once

#ifdef  _WIN32
    #include <Windows.h>
	typedef   char   int8;
	typedef   unsigned char  uint8;
	typedef   short  int16 ;
	typedef   unsigned short uint16 ;
	typedef   int    int32 ;
	typedef   unsigned int   uint32 ;
	typedef   __int64   int64 ;
	typedef   unsigned  __int64  uint64 ;
	typedef   HMODULE    HLIB;

#elif  defined(__linux__)
	#include <stdint.h>
	#include <pthread.h>
	#include <semaphore.h>
	#include <signal.h>
	#include <unistd.h>
	#include <errno.h>
	#include <semaphore.h>
	#include <stdarg.h>

	typedef   int8_t     int8   ;
	typedef   uint8_t    uint8  ;
	typedef   int16_t    int16  ;
	typedef   uint16_t   uint16 ;
	typedef   int32_t    int32  ;
	typedef   uint32_t   uint32  ;
	typedef   int64_t    int64  ;
	typedef   uint64_t   uint64 ;
#elif  defined(__APPLE__)
	#include <stdint.h>
	#include <pthread.h>
	#include <semaphore.h>
	#include <signal.h>
	#include <unistd.h>
	#include <errno.h>
	#include <semaphore.h>
	#include <stdarg.h>

	typedef   int8_t     int8   ;
	typedef   uint8_t    uint8  ;
	typedef   int16_t    int16  ;
	typedef   uint16_t   uint16 ;
	typedef   int32_t    int32  ;
	typedef   uint32_t   uint32 ;
	typedef   int64_t    int64  ;
	typedef   uint64_t   uint64 ;
#endif

#if _WIN32 != 1 || _MSC_VER >= 1600
#include <memory>
#include <functional>

#define CSharedPtr		std::shared_ptr
#define CFunction		std::function
#define CNull			nullptr
#define CBind			std::bind
#define CPlaceholders   std::placeholders::
#define CMakePtr		std::make_shared

#else
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>  
#include <boost/function.hpp> 
#include <boost/make_shared.hpp>

#define CSharedPtr boost::shared_ptr
#define CFunction  boost::function
#define CNull      NULL
#define CBind      boost::bind
#define CPlaceholders       
#define CMakePtr   boost::make_shared
#endif