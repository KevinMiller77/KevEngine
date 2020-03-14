#ifndef __KEY_EVENT__
#define __KEY_EVENT__

#include "Event.h"

class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keycode)
			: keyCode(keycode) {}

		int keyCode;
	public:
		inline int GetKeyCode() const { return keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
};

class KeyPressedEvent : public KeyEvent
{
	int repeatCount;
public:
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), repeatCount(repeatCount) {}

	inline int GetRepeatCount() const { return repeatCount; }

	const char* ToString() const override
	{
		char* ss;
        sprintf(ss, "KeyPressedEvent: %d ( %d repeats)\n", keyCode, repeatCount);
		return ss;
	}

	EVENT_CLASS_TYPE(KeyPressed);
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keycode)
		: KeyEvent(keycode) {}

	const char* ToString() const override
	{
		char* ss;
        sprintf(ss, "KeyReleasedEvent: %d\n", keyCode);
		return ss;
	}

	EVENT_CLASS_TYPE(KeyReleased);
};


class KeyHeldEvent : public KeyEvent
{
public:
	KeyHeldEvent(int keycode)
		: KeyEvent(keycode) {}

	const char* ToString() const override
	{
		char* ss;
        sprintf(ss, "KeyHeldEvent: %d\n", keyCode);
		return ss;
	}

	EVENT_CLASS_TYPE(KeyHeld);
};

#endif