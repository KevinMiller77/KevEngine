#ifndef __GAME_LAYER__
#define __GAME_LAYER__


#include <events/InputCodes.h>
#include <events/MouseEvent.h>
#include <events/KeyEvent.h>
#include <events/WindowEvent.h>
#include <graphics/renderables/Sprite.h>
#include <graphics/renderables/PhysicsSprite.h>
#include <graphics/layers/Group.h>
#include <graphics/layers/Layer.h>
#include <graphics/renderer/Kev2DRenderer.h>
#include <math/math.h>
#include <utils/Logging.h>
#include <utils/Timer.h>
#include <graphics/cameras/FollowRenderableCamera.h>
#include <../ext/imgui/imgui.h>
#include <imgui/KevImGuiLog.h>

#define GAME_KEY_DEBOUNCE_TIME 0.2f
#define GAMESPACE_X 16.0f
#define GAMESPACE_Y 9.0f

struct Move
{
    Move(Renderable2D* Renderable, Vec2u OldTile)
    {
        renderable = Renderable;
        oldTile = OldTile;
    }
    Renderable2D* renderable;
    Vec2u oldTile;
};

class GameLayer : public Layer
{
    Vec2u screenSize;
    Vec2f screenExtremes;
    //Mouse pos adjusted to be in world space (-X, X, -Y, Y)
    Vec2f mousePos;

    bool MouseScroll(MouseScrolledEvent& e);
    bool MouseMove(MouseMovedEvent& e);
    bool WindowResize(WindowResizeEvent& e);
    bool KeyDown(KeyPressedEvent& e);
    bool MouseButton(MouseButtonPressedEvent& e);

    bool ImGuiEnabled = true;
    bool KevImGuiLogOpen = true;

    bool paused = false;

    unsigned int vpTexture;

    KevImGuiLog log;

    FollowRenderableCamera camera;
    Group* guideGrids;
    Group* scene;
    
    Group* tilemap[32][18];
    
    Renderable2D* selectedTile = nullptr;
    Renderable2D* cursor = nullptr;
    int selectedTilesTilePos[2] = {0, 0};
    int brushTilesheetPos[2] = {1, 11};
    Vec2u brushPos = Vec2u(0, 0);
    int copiedTilePos[2] = {0, 0};
    bool painting = false;
    bool addingLayer = false;
    
    std::vector<Move> undoCache;
    
    Renderable2D* player;
    Timer updateTime;
    Timer keyTimeout;

public:
    GameLayer(Window* Parent, unsigned int Shader, Vec2u ScreenSize, Vec2f ScreenExtremes = Vec2f(GAMESPACE_X, GAMESPACE_Y));
    ~GameLayer() override;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate() override;
    virtual void OnDraw() override;
    // virtual void Render() override;
    virtual void OnEvent(Event& e);
    virtual void OnImGuiRender() override;

    inline bool IsImGuiEnabled()   { return ImGuiEnabled; }
    inline void SetImGuiEnabled(bool state) { ImGuiEnabled = state; }
    
    void SaveTilemap();
    void LoadTilemap();
    
    void BuildTilemapSelector();
    void BuildCurrentPaintbrush();
    void BuildTileLayerSelector();
    
    void StartSelecting();
    void StopSelecting();
    
    void PaintMousedTile(bool force = false);
    void PaintSelectedTile();

};

#endif
