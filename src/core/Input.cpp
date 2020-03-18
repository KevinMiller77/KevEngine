#include "Input.h"
#include <core/Core.h>

#ifdef KEV_PLATFORM_WINDOWS
#include <windows.h>
#endif

Input* Input::input = new Input;