#pragma once

#ifdef HG_PLATFORM_WINDOWS
#if HG_DYNAMIC_LINK
	#ifdef HG_BUILD_DLL
		#define HG_API __declspec(dllexport)
	#else
		#define HG_API __declspec(dllimport)
	#endif
#else
	#define HG_API
#endif
#else
#error HG only supports Windows!
#endif // !HG_PLATFORM_WINDOWS

#ifdef HG_DEBUG
	#define HG_ENABLE_ASSERTS
#endif // HG_DEBUG


#ifdef HG_ENABLE_ASSERTS
	#define HG_ASSERT(x, ...){if(!(x)){HG_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
	#define HG_CORE_ASSERT(x, ...){if(!(x)){HG_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
#else
	#define HG_ASSERT(x, ...)
	#define HG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HG_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)