#include "KevEngine.h"
#include "KevInput.h"

KevInput* KevInput::s_Input = new KevInput;

bool KevInput::IsKeyPressedInt(KeyCode key) 
{
    auto win = (GLFWwindow*)(KevEngine::Get()->GetWindow().GetNativeWindow());
    auto state = glfwGetKey(win, (int)key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;

}
bool KevInput::IsMouseButtonPressedInt(MouseCode key) 
{ 
    auto win = (GLFWwindow*)(KevEngine::Get()->GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(win, (int)key);
    return state == GLFW_PRESS;
}

Vec2f KevInput::GetMousePosInt() 
{ 
    auto win = (GLFWwindow*)(KevEngine::Get()->GetWindow().GetNativeWindow());
    double x, y;
    glfwGetCursorPos(win, &x, &y);
    return Vec2f(x, y);
}