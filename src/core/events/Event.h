#ifndef __EVENT__
#define __EVENT__

#include "../Core.h"

#include <functional>

enum class EventType
{
    None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	PlatformTick, PlatformUpdate, PlatformRender,
	KeyPressed, KeyReleased, KeyHeld,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication    = BIT(0),
	EventCategoryInput          = BIT(1),
	EventCategoryKeyboard       = BIT(2),
	EventCategoryMouse          = BIT(3),
	EventCategoryMouseButton    = BIT(4)
};


//Check the type and name of any event
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
                                                    virtual EventType GetEventType() const override { return GetStaticType(); } \
                                                    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(cat) virtual int GetCategoryFlags() const override { return cat; }

class Event
{
    friend class EventDispatcher;
protected:
    bool eventHandled;

public:
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual const char* ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory cat)
    {
        return GetCategoryFlags() & cat;
    }

};


class EventDispatcher
{
    Event& curEvent;

    template<typename T>
    using EventFunc = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
        : curEvent(event)
    {
    }

    template<typename T>
    bool Dispatch(EventFunc<T> func)
    {
        if (curEvent.GetEventType() == T::GetStaticType())
        {
            curEvent.eventHandled = func(*(T)&curEvent);
            return true;
        }
        return false;
    }

};

#endif