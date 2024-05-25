#pragma once

#include <memory>


#ifdef MABENGINE_PLATFORM_WINDOWS
	#ifdef MABENGINE_INCLUDE_AS_DLL
		//If we want to include mabengine as DLL we have to define MABENGINE_INCLUDE_AS_DLL precompile variable
		#ifdef INSIDE_MABENGINE_DLL
			#define MABENGINE_API __declspec(dllexport)
		#else
			#define MABENGINE_API __declspec(dllimport)
		#endif
	#else
		#define MABENGINE_API
	#endif
#else
	#error your platform is not defined
#endif


#ifdef MAB_ENABLE_ASSERTS
	#define MAB_ASSERT(x, ...) { if (!x) { MAB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MAB_CORE_ASSERT(x, ...) { if (!x) { MAB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MAB_ASSERT(x, ...)
	#define MAB_CORE_ASSERT(x, ...) 
#endif

#define BIT(x)	(1 << x)

#define MAB_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace MABEngine{
	namespace Core {
		template<typename T>
		using Scope = std::unique_ptr<T>;
	
		template<typename T, typename ... Args>
		constexpr Scope<T> CreateScope(Args&& ... args) {
			return std::make_unique<T>(std::forward<Args>(args)...);
		}


		template<typename T>
		using Ref = std::shared_ptr<T>;

		template<typename T, typename ... Args>
		constexpr Ref<T> CreateRef(Args&& ... args) {
			return std::make_shared<T>(std::forward<Args>(args)...);
		}
	}
}
