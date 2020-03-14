#ifndef __WINDOW__
#define __WINDOW__

class Window 
{
private:
    struct Properties
    {
        const char* title = "KevEngine";
        unsigned int width = 1280;
        unsigned int height = 720;
    } props;

public:
    using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

};


#endif