#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

#define WINDOW_CLASS_NAME "KevEngineTestWindowClass"

#define TICK_RATE 1000;
#define FRAME_RATE 60;

if (!glfwInit())
{
    LOG_INF()
}