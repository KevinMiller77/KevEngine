#ifndef __KEV_GAME__
#define __KEV_GAME__

#include <windows.h>
#include "KevEngine.h"

#define SCREEN_SIZE_X 960
#define SCREEN_SIZE_Y 540

class KevGame : public KevEngine
{
public:
    KevGame(int screenX, int screenY) : KevEngine(screenX, screenY) {}

    void OnGameStart() override;
    void Draw() override;
    void OnTick() override;
    void OnUpdate() override;
    void ProcessInput(InputInformation in) override;

    void ResetEngine() override; 
};

#endif