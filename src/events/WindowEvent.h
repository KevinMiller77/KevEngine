#ifndef __WINDOW_EVENT__
#define __WINDOW_EVENT__

#include "Event.h"

//WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved

class WindowResizeEvent : public Event
{
protected:
    Vec2u screenSize;

public:
    WindowResizeEvent(Vec2u newSize)
        : screenSize(newSize)   {}

    inline Vec2u getScreenSize() const { return screenSize; } 

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class WindowFocusEvent : public Event
{
public:
    WindowFocusEvent() {}

    EVENT_CLASS_TYPE(WindowFocus)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class WindowLostFocusEvent : public Event
{
public:
    WindowLostFocusEvent() {}

    
    EVENT_CLASS_TYPE(WindowFocus)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class WindowCloseEvent : public Event
{

public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
};


#endif