#ifndef __KEV_INPUT__
#define __KEV_INPUT__

#include <core/math/math.h>
#include <core/Core.h>
#include <map>

#ifdef KEV_PLATFORM_WINDOWS
#include <WinUser.h>
#include <core/events/WindowsInputCodes.h>
#else
#error "Unknown platform!"
#endif


class Input
{
    std::map<KeyCode, bool> keys;
    std::map<MouseCode, bool> mouseButtons;
    Vec2u mousePos;

public:
    Input()
    {
        for (int i = 0; i < 0xFF; i++)
        {
            keys[(KeyCode)i] = false;
            mouseButtons[(MouseCode)i] = false;
            mousePos = Vec2u(0, 0);
        }
    }

    inline static bool IsKeyPressed(KeyCode key) {return input->IsKeyPressedInt(key); }
    inline static bool IsMouseButtonPressed(MouseCode key) { return input->IsMouseButtonPressedInt(key); }

    inline static void SetKeyPressed(KeyCode key) { input->SetKeyPressedInt(key); }    
    inline static void SetKeyReleased(KeyCode key) { input->SetKeyReleasedInt(key); }

    inline static void SetMouseButtonPressed(MouseCode key) { input->SetMouseButtonPressedInt(key); }    
    inline static void SetMouseButtonReleased(MouseCode key) { input->SetMouseButtonReleasedInt(key); }
    
    inline static Vec2u GetMousePos() { return input->GetMousePosInt(); }
    inline static void SetMousePos(Vec2u newPos) { input->SetMousePosInt(newPos); }

#ifdef KEV_PLATFORM_WINDOWS
    inline bool IsKeyPressedInt(KeyCode key) { short keystate = GetAsyncKeyState((int)key); return (1 << 15 ) & keystate; }
#else
    inline bool IsKeyPressedInt(KeyCode key) {return keys[key]; }
#endif
    inline bool IsMouseButtonPressedInt(MouseCode key) { return mouseButtons[key]; }

    inline void SetKeyPressedInt(KeyCode key) { keys[key] = true; }    
    inline void SetKeyReleasedInt(KeyCode key) { keys[key] = false; }

    inline void SetMouseButtonPressedInt(MouseCode key) { mouseButtons[key] = true; }    
    inline void SetMouseButtonReleasedInt(MouseCode key) { mouseButtons[key] = false; }
    
    inline Vec2u GetMousePosInt() { return mousePos; }
    inline void SetMousePosInt(Vec2u newPos) { mousePos = newPos; }

    static Input* input;
};

#endif