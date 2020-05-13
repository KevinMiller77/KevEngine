#ifndef __KEV_WINDOW__
#define __KEV_WINDOW__

#include <functional>

#include <events/Event.h>
#include <events/KeyEvent.h>
#include <events/MouseEvent.h>
#include <events/WindowEvent.h>



//Information a generic window will need for construction
struct WindowInfo
{
	bool windowed;

    const char* Title;
    unsigned int Width;
    unsigned int Height;

    WindowInfo(const char* title = "Kev Engine", unsigned int width = 1280, unsigned int height = 720)
        : Title(title), Width(width), Height(height) {}
};

//Platform independent window function.
//This will represent the entry point to our engine
//This class should be overridden for the platform being used
class Window
{
public:
	Window() {};
    
	using EventCallbackFn = std::function<void(Event&)>;

	virtual void OnUpdate() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	
	virtual unsigned int* GetWidthPtr() const = 0;
	virtual unsigned int* GetHeightPtr() const = 0;

	// Window attributes
	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	virtual void* GetNativeWindow() = 0;
	virtual void* GetContext() = 0;

	virtual void SetView(int W, int H) = 0;
    virtual inline bool IsWindowed() = 0;

	virtual void ToggleFullscreen() = 0;
	virtual void CallWindowHints() = 0;

	static Scope<Window> Create(const WindowInfo& inf = WindowInfo());
};

#endif
