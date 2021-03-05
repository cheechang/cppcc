#pragma once
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