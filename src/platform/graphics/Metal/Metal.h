#ifndef __METAL_CORE__
#define __METAL_CORE__

#include <core/KevEngine.h>
#include <platform/OS/Window/MacOS/MacWindow.h>

#ifdef KEV_RENDERAPI_METAL
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#endif
#ifdef KEV_PLATFORM_MACOS
    #import <Metal/Metal.h>
    #import <QuartzCore/QuartzCore.h>
#endif

#define GET_GLFW_METAL_WINDOW() static_cast<GLFWwindow*>(KevEngine::Get()->GetWindow()->GetNativeWindow())
#define GET_METAL_DEVICE() ((MacWindow*)(KevEngine::Get()->GetWindow()))->GetDevice()
#define GET_METAL_QUEUE() ((MacWindow*)(KevEngine::Get()->GetWindow()))->GetQueue()
#define GET_METAL_LAYER() ((MacWindow*)(KevEngine::Get()->GetWindow()))->GetLayer()

#endif
