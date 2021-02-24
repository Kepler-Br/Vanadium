#ifndef VANADIUM_ASSERT_H
#define VANADIUM_ASSERT_H

#include "Log.h"
#ifdef VANADIUM_DEBUG
    #if defined(VANADIUM_PLATFORM_WINDOWS)
		#define VAN_DEBUGBREAK() __debugbreak()
	#elif defined(VANADIUM_PLATFORM_LINUX)
		#include <csignal>
		#define VAN_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
    #define VANADIUM_ENABLE_ASSERTS
#else
    #define VAN_DEBUGBREAK()
#endif

#ifdef VANADIUM_ENABLE_ASSERTS
    #define VAN_ENGINE_ASSERT(condition, ...) if (!condition) { VAN_ENGINE_ERROR(__VA_ARGS__); VAN_DEBUGBREAK(); }
    #define VAN_ASSERT(condition, ...) if (!condition) { VAN_USER_ERROR(__VA_ARGS__); VAN_DEBUGBREAK(); }
#else
    #define VAN_ENGINE_ASSERT(condition, ...) if (!condition) VAN_ENGINE_ERROR(__VA_ARGS__);
    #define VAN_ASSERT(condition, ...) if (!condition) VAN_USER_ERROR(__VA_ARGS__);
#endif

#endif //VANADIUM_ASSERT_H
