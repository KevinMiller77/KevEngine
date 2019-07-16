#ifndef __TLETC_LOGGING__
#define __TLETC_LOGGING__

#define DEBUG_LEVEL 3   //(Debugging level; 1) Error  2) Warning 3) Info
                        //                  4) Debug 5) Verbose 6)Too Much Info

//Error Log
#if DEBUG_LEVEL > 0
#define LOGE(x) printf("[TLETC] E: "); printf(x);
#else
#define LOGE(x)
#endif

//Warning Log
#if DEBUG_LEVEL > 1
#define LOGW(x) printf("[TLETC] W: "); printf(x);
#else
#define LOGW(x)
#endif

//Info Log
#if DEBUG_LEVEL > 2
#define LOGI(x) printf("[TLETC] I: "); printf(x);
#else
#define LOGI(x)
#endif

//Debug Log
#if DEBUG_LEVEL > 3
#define LOGD(x) printf("[TLETC] D: "); printf(x);
#else
#define LOGD(x)
#endif

//Verbose Log
#if DEBUG_LEVEL > 4
#define LOGV(x) printf("[TLETC] V: "); printf(x);
#else
#define LOGV(x)
#endif

//TMI Log
#if DEBUG_LEVEL > 5
#define LOGT(x) printf("[TLETC] TMI: "); println(x);
#else
#define LOGT(x)
#endif


#endif