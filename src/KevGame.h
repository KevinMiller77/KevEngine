#ifndef __KEV_GAME__
#define __KEV_GAME__

#include <windows.h>
#include "TLETC.h"

#define SCREEN_SIZE_X 960
#define SCREEN_SIZE_Y 540

class KevGame : public TLETC
{
public:
    KevGame(int screenX, int screenY) : TLETC(screenX, screenY) {}

    void OnGameStart() override;
    void Draw() override;
    void OnTick() override;
    void OnUpdate() override;
    void ProcessInput(InputInformation in) override;

    void ResetEngine() override; 
};

#endif