#ifndef __ENTRY_POINT__
#define __ENTRY_POINT__

extern KevEngine* CreateApplication();

int main(int argv, char** argc)
{
//Hot swappable game scripting
    printf("Main\n");
    auto app = CreateApplication();
    printf("Running app\n");
#ifdef KEV_PLATFORM_EM
    emscripton_set_main_loop(app->Run, 0, 1);
#else
    app->Run();
#endif
    delete app;
    
    return 0;
}

#endif