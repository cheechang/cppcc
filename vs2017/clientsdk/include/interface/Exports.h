#pragma once
#ifdef _WIN32
	#ifdef CONTROL_EXPORT
        #define  CONTROL_EXPORT_API __declspec(dllexport)
	#else
        #define  CONTROL_EXPORT_API __declspec(dllimport)
	#endif
#else
	#define  CONTROL_EXPORT_API
#endif