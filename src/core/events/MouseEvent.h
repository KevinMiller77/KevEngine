#include "Event.h"

#include "../math/math.h"

//MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

class MouseButtonPressedEvent : public Event
{
    int pressedButton;

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)

public:
    MouseButtonPressedEvent(int button)
    {
        pressedButton = button;
    }
    
    
	EVENT_CLASS_TYPE(MouseButtonPressed);
};