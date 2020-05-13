#include "Window.h"

#include <core/KevInput.h>

#include <platform/OS/Window/Windows/WindowsWindow.h>
#include <platform/OS/Window/Linux/LinuxWindow.h>
#include <platform/OS/Window/MacOS/MacWindow.h>


Scope<Window> Window::Create(const WindowInfo& inf)
{
#ifdef KEV_PLATFORM_WINDOWS
	return CreateScope<WindowsWindow>(inf);
#elif defined KEV_PLATFORM_LINUX
	return CreateScope<LinuxWindow>(inf);
#elif defined KEV_PLATFORM_MACOS
    return CreateScope<MacWindow>(inf);
#endif
}
