#include "Window.h"

#include <core/KevInput.h>

#include <platform/Windows/WindowsWindow.h>


Scope<Window> Window::Create(const WindowInfo& inf)
{
	return CreateScope<WindowsWindow>(inf);
}