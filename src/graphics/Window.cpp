#include "Window.h"

#include <core/KevInput.h>

#include <platform/Windows/WindowsWindow.h>
#include <platform/Linux/LinuxWindow.h>


Scope<Window> Window::Create(const WindowInfo& inf)
{
#ifdef KEV_PLATFORM_WINDOWS
	return CreateScope<WindowsWindow>(inf);
#endif
#ifdef KEV_PLATFORM_LINUX
	return CreateScope<LinuxWindow>(inf);
#endif
}