#pragma once

#ifdef MABENGINE_PLATFORM_WINDOWS;
	#ifdef MABENGINE_BUILD_DLL
		#define MABENGINE_API __declspec(dllexport)
	#else
		#define MABENGINE_API __declspec(dllimport)
	#endif
#else
	#error your platform is not defined
#endif