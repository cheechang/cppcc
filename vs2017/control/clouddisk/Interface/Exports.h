#pragma once
#ifdef _WIN32
	#ifdef CLOUDDISK_EXPORT
		#define  CLOUDDISK_EXPORT_API __declspec(dllexport)
	#else
		#define  CLOUDDISK_EXPORT_API __declspec(dllimport)
        #define  CLOUDDISK_TURN_ON
		#pragma comment(lib,"clouddisk.lib")
	#endif
#else
	#define  CONTROL_EXPORT_API
#endif