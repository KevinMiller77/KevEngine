#ifndef __ENTRY_POINT__
#define __ENTRY_POINT__

#include "Core.h"

#ifdef KEV_PLATFORM_WINDOWS

extern KevEngine* CreateApplication();

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    printf("Main\n");
    auto app = CreateApplication();

    printf("Running app\n");
    app->Run();

    delete app;
}

#endif
#endif