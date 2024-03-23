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


#ifdef MAB_ENABLE_ASSERTS
	#define MAB_ASSERT(x, ...) { if !(x) { MAB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MAB_CORE_ASSERT(x, ...) { if !(x) { MAB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MAB_ASSERT(x, ...) 
	#define MAB_CORE_ASSERT(x, ...) 
#endif

#define BIT(x)	(1 << x)