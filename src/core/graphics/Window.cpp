#include "Window.h"

#ifdef KEV_PLATFORM_WINDOWS
#include "../../platform/Windows/WindowsWindow.h"
#endif

Scope<Window> Window::Create(const WindowInfo& inf)
{
#ifdef KEV_PLATFORM_WINDOWS
	return CreateScope<WindowsWindow>(inf);
#else
	LOG_ERR("Unknown platform!");
	return nullptr;
#endif
}