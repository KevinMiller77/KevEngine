#include "Window.h"

#include <core/KevInput.h>

#include <platform/OS/Window/Windows/WindowsWindow.h>
#include <platform/OS/Window/Linux/LinuxWindow.h>
#include <platform/OS/Window/MacOS/MacWindow.h>

Window* Window::Create(const WindowInfo& inf)
{
#ifdef KEV_PLATFORM_WINDOWS
	return new WindowsWindow(inf);
#elif defined KEV_PLATFORM_LINUX
	return new LinuxWindow(inf);
#elif defined KEV_PLATFORM_MACOS
    #if defined KEV_RENDERAPI_METAL
        return new MacWindow(inf);
    #else
        return new WindowsWindow(inf);
    #endif
#endif
}
