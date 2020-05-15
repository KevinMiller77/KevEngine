#ifndef __CORE__
#define __CORE__

#define KEV_ENGINE_WINDOW_X 1280
#define KEV_ENGINE_WINDOW_Y 720

#include <memory>
#include <functional>
#include "utils/MemoryTracker.h"

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#define KEV_PLATFORM_WINDOWS
	#define KEV_RENDERAPI_GL
	#include <windows.h>
	#ifdef _WIN64
		/* Windows x64  */
		#define KEV_PLATFORM_WIN64
	#else
		/* Windows x86 */
		#define KEV_PLATFORM_WIN32
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#define KEV_PLATFORM_APPLE
	// TODO: Go to metal
	 #define KEV_RENDERAPI_METAL
//	#define KEV_RENDERAPI_GL
	#if TARGET_IPHONE_SIMULATOR == 1
		#define KEV_PLATFORM_IOS_SIM
		#error "iOS sim is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define KEV_PLATFORM_IOS
		#error "iOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define KEV_PLATFORM_MACOS
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define KEV_PLATFORM_ANDROID
	#define KEV_RENDERAPI_GLES
	#error "Android is not supported!"
#elif defined(__linux__)
	#define KEV_PLATFORM_LINUX
	#define KEV_RENDERAPI_GL
#elif defined(__EMSCRIPTEN__)
	#define KEV_RENDERAPI_GLES
	#define KEV_PLATFORM_EM
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

//Make sure that GL is included when using GLES
#ifdef KEV_RENDERAPI_GLES
    #define KEV_RENDERAPI_GL
#endif

//#undef KEV_RENDERAPI_GL

#define BIT(x) (1 << x)

#define KEV_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
#endif
