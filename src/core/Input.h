#ifndef __KEV_INPUT__
#define __KEV_INPUT__

#include <core/math/math.h>
#include <core/Core.h>

#ifdef KEV_PLATFORM_WINDOWS
#include <core/events/WindowsInputCodes.h>
#else
#error "Unknown platform!"
#endif

class Input
{
    bool keys[0xFF];
    bool mouseButtons[0xFF];
    Vec2u mousePos;

public:
    Input()
    {
        for (int i = 0; i < 0xFF; i++)
        {
            keys[i] = false;
            mouseButtons[i] = false;
            mousePos = Vec2u(0, 0);
        }
    }

    inline static bool IsKeyPressed(KeyCode key) {return input.IsKeyPressedInt(key); }
    inline static bool IsMouseButtonPressed(MouseCode key) { return input.IsMouseButtonPressedInt(key); }

    inline static void SetKeyPressed(KeyCode key) { input.SetKeyPressedInt(key); }    
    inline static void SetKeyReleased(KeyCode key) { input.SetKeyReleasedInt(key); }

    inline static void SetMouseButtonPressed(MouseCode key) { input.SetMouseButtonPressedInt(key); }    
    inline static void SetMouseButtonReleased(MouseCode key) { input.SetMouseButtonReleasedInt(key); }
    
    inline static Vec2u GetMousePos() { return input.GetMousePosInt(); }
    inline static void SetMousePos(Vec2u newPos) { input.SetMousePosInt(newPos); }

    inline bool IsKeyPressedInt(KeyCode key) {return keys[(int)key]; }
    inline bool IsMouseButtonPressedInt(MouseCode key) { return mouseButtons[(int)key]; }

    inline void SetKeyPressedInt(KeyCode key) { keys[(int)key] = true; }    
    inline void SetKeyReleasedInt(KeyCode key) { keys[(int)key] = false; }

    inline void SetMouseButtonPressedInt(MouseCode key) { mouseButtons[(int)key] = true; }    
    inline void SetMouseButtonReleasedInt(MouseCode key) { mouseButtons[(int)key] = false; }
    
    inline Vec2u GetMousePosInt() { return mousePos; }
    inline void SetMousePosInt(Vec2u newPos) { mousePos = newPos; }

    static Input input;
};

#endif