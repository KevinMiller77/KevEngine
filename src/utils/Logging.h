#ifndef __KevEngine_LOGGING__
#define __KevEngine_LOGGING__

#define DEBUG_LEVEL 4   //(Debugging level; 1) Error  2) Warning 3) Info
//                  4) Debug 5) Verbose 6)Too Much Info

#ifdef DEBUG_LEVEL
#include <stdio.h>
#endif

#ifdef DEBUG_LEVEL
#define LOG(type, ...) LOG_##type(__VA_ARGS__)
#else
#define LOG(type, ...)
#endif

//Error Log
#if DEBUG_LEVEL > 0
#define LOG_ERR(...) printf("[KevEngine] E: " __VA_ARGS__)
#else
#define LOG_ERR(...)
#endif

//Warning Log
#if DEBUG_LEVEL > 1
#define LOG_WRN(...) printf("[KevEngine] W: " __VA_ARGS__)
#else
#define LOG_WRN(...)
#endif

//Info Log
#if DEBUG_LEVEL > 2
#define LOG_INF(...) printf("[KevEngine] I: " __VA_ARGS__)
#else
#define LOG_INF(...)
#endif

//Debug Log
#if DEBUG_LEVEL > 3
#define LOG_DBG(...) printf("[KevEngine] D: " __VA_ARGS__)
#else
#define LOG_DBG(...)
#endif

//Verbose Log
#if DEBUG_LEVEL > 4
#define LOG_VER(...)  printf("[KevEngine] V: " __VA_ARGS__)
#else
#define LOG_VER(...)
#endif

//TMI Log
#if DEBUG_LEVEL > 5
#define LOG_TMI(...) printf("[KevEngine] TMI: " __VA_ARGS__)
#else
#define LOG_TMI(...)
#endif


#endif