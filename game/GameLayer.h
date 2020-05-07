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

enum class BrushFunction
{
    NONE,
    PAINT,
    REMOVE,
    SELECT
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
    Vec2u selectedTilesTilePos = Vec2u(0, 0);
    Vec2u brushTilesheetPos = Vec2u(1, 11);
    Vec2u brushPos = Vec2u(0, 0);
    Vec2u brushSize = Vec2u(0, 0);
    Vec2u copiedTilePos = Vec2u(0, 0);
    
    BrushFunction brushMode = BrushFunction::NONE;
    Vec2u hotbarItems[10] = {Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12), Vec2u(22, 12)};
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
    
    inline Renderable2D* GetTopLevelParent(Renderable2D* child)
    {
        Renderable2D* lastRenderable = child;
        Renderable2D* curRenderable = child;
        while (curRenderable->GetParent() != nullptr)
        {
            lastRenderable = curRenderable;
            curRenderable = curRenderable->GetParent();
        }
        
        return curRenderable;
    }
    
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
