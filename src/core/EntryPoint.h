#ifndef __ENTRY_POINT__
#define __ENTRY_POINT__

extern KevEngine* CreateApplication();

int main(int argv, char** argc)
{
//Hot swappable game scripting
#if 0
    
#else
    printf("Main\n");
    auto app = CreateApplication();

    printf("Running app\n");
    app->Run();

    delete app;
#endif
    return 0;
}

#endif