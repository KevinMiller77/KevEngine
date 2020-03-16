#ifndef __MOUSE_EVENT__
#define __MOUSE_EVENT__

#include "Event.h"

//MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

class MouseMovedEvent : public Event
{
protected:
    Vec2u position;

public:
    MouseMovedEvent(Vec2u newPos)
        :   position(newPos)  {}

    inline const Vec2u getPos() const { return position; }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MouseScrolledEvent : public Event
{
protected:
    int XOffset, YOffset;

public:
    MouseScrolledEvent(int X, int Y)
        :   XOffset(X), YOffset(Y)  {}

    inline const int getXOffset() const { return XOffset; }
    inline const int getYOffset() const { return YOffset;}

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MouseButtonEvent : public Event
{
protected:
    MouseCode ButtonIQ;

public:
    MouseButtonEvent(MouseCode buttonInQuestion)
        :   ButtonIQ(buttonInQuestion) {}

    inline MouseCode getButton() { return ButtonIQ; }
    
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};


class MouseButtonPressedEvent : public MouseButtonEvent
{

public:
    MouseButtonPressedEvent(MouseCode button)
        : MouseButtonEvent(button)  {}
    
	EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{

public:
    MouseButtonReleasedEvent(MouseCode button)
        : MouseButtonEvent(button)  {}
    
	EVENT_CLASS_TYPE(MouseButtonReleased);
};

#endif