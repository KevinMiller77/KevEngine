#include "Window.h"
#include <core/Input.h>

#ifdef KEV_PLATFORM_WINDOWS
#include "../../platform/Windows/WindowsWindow.h"
#endif

Scope<Window> Window::Create(const WindowInfo& inf)
{
#ifdef KEV_PLATFORM_WINDOWS
printf("Create window");
	return CreateScope<WindowsWindow>(inf);
#else
	LOG_ERR("Unknown platform!");
	return nullptr;
#endif
}