#ifndef __ENTRY_POINT__
#define __ENTRY_POINT__

#include "Core.h"

#ifdef KEV_PLATFORM_WINDOWS

extern MainApp* CreateApplication();

int main(int argc, char** argv)
{
    auto app = CreateApplication

    app->Run();

    delete app;
}

#endif
#endif