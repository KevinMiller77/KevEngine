#include "KevEngine.h"
#include "KevInput.h"

KevInput* KevInput::s_Input = new KevInput;

bool KevInput::IsKeyPressedInt(KeyCode key) 
{
    Window* win = &(KevEngine::Get()->GetWindow());
    GLFWwindow* window = (GLFWwindow*)(win->GetNativeWindow());
    auto state = glfwGetKey(window, (int)key);
    return state == GLFW_PRESS | GLFW_REPEAT;

}
bool KevInput::IsMouseButtonPressedInt(MouseCode key) 
{ 
    Window* win = &(KevEngine::Get()->GetWindow());
    GLFWwindow* window = (GLFWwindow*)(win->GetNativeWindow());
    auto state = glfwGetMouseButton(window, (int)key);
    return state == GLFW_PRESS | GLFW_REPEAT;
}

Vec2f KevInput::GetMousePosInt() 
{ 
    Window* win = &(KevEngine::Get()->GetWindow());
    GLFWwindow* window = (GLFWwindow*)(win->GetNativeWindow());
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return Vec2f(x, y);
}