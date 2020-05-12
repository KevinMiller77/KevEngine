#include "Window.h"

#include <core/KevInput.h>

#include <platform/OS/Windows/WindowsWindow.h>
#include <platform/OS/Linux/LinuxWindow.h>


Scope<Window> Window::Create(const WindowInfo& inf)
{
#ifdef KEV_PLATFORM_WINDOWS
	return CreateScope<WindowsWindow>(inf);
#endif
#ifdef KEV_PLATFORM_LINUX
	return CreateScope<LinuxWindow>(inf);
#endif
#ifdef KEV_PLATFORM_MACOS
    return CreateScope<WindowsWindow>(inf);
#endif
}
