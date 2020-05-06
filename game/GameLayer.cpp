#include "GameLayer.h"
#include <algorithm>
#include <fstream>
#include <iostream> 
#include <core/KevInput.h>

#include <glad/glad.h>


GameLayer::GameLayer(Window* Parent, unsigned int Shader, Vec2u ScreenSize, Vec2f ScreenExtremes)
    : Layer(Parent, new Kev2DRenderer((int*)Parent->GetWidthPtr(), (int*)Parent->GetHeightPtr()), Shader), screenSize(ScreenSize), screenExtremes(ScreenExtremes), camera(ScreenExtremes.x, ScreenExtremes.y)
{
    //Enable blending of the alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    keyTimeout.Start();
}

GameLayer::~GameLayer()
{
    for (Renderable2D* renderable : renderables)
    {
        delete renderable;
    }
}

void GameLayer::OnAttach()
{
    updateTime.Reset();
    undoCache.clear();
    //Setup textures, can't be used without them
    textures.NewTexture("tilemap", "resources/tilesheets/towerDefense_tilesheet@2.png", 128, Vec2f(1.0f, 0.0f));
    textures.NewTexture("dude", "resources/textures/KevDude.png");
    textures.NewTexture("cursor", "resources/textures/EditorCursor.png");

    cursor = new Sprite(0, 0, 1, 1, textures.GetTexture("cursor"));
    
    scene = new Group(Mat4f::translation(Vec3f(-screenExtremes.x, -screenExtremes.y, 0.0f)));
    
    for (float x = 0; x < GAMESPACE_X * 2; x += 1)
    {
        for (float y = 0; y < GAMESPACE_Y * 2; y += 1)
        {
            Group* newGroup = new Group(Mat4f::translation(Vec3f((float)x, (float)y, 0)));
            newGroup->Add(new Sprite(0, 0, 1, 1, textures.GetTexture("tilemap"), Vec2u(1, 11)));
            if (x == 0 && y == 0)
            {
                newGroup->Add(new Sprite(0, 0, 1, 1, textures.GetTexture("tilemap"), Vec2u(0, 0)));
            }
            tilemap[(int)(x + 0.5f)][(int)(y + 0.5f)] = newGroup;
            scene->Add(tilemap[(int)(x + 0.5f)][(int)(y + 0.5f)]);
        }
    }
    
    Add(scene);

    updateTime.Reset();
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate()
{
    if (paused)
    {
        return;
        updateTime.Reset();
    }
    //Begin frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.OnUpdate();
    
    ShaderProgram::EnableShaderProgram(shader);
    ShaderProgram::SetShaderUniformMat4(shader, "pr_matrix", camera.GetCamera().GetViewProjectionMatrix());
    
    ImGuiIO io = ImGui::GetIO();
    if(!io.WantCaptureMouse)
    {
        Manager.MouseCheck(mousePos);
    }
    Manager.CollisionCheck();
    Manager.OnUpdate();

    updateTime.Reset();
    PaintMousedTile();
}

void GameLayer::OnImGuiRender() 
{
    if (!IsImGuiEnabled())
    {
        return;
    }
    
    log.Update(KevImGuiLogOpen);
    
    BuildCurrentPaintbrush();
    BuildTilemapSelector();
    BuildTileLayerSelector();

}

void GameLayer::BuildTilemapSelector()
{
    ImGui::Begin("Tilemap selector");
    
    if (textures.GetTexture("tilemap")->IsTilesheet())
    {
        
        int sheetWidth = 23 * 128;
        int sheetHeight = 13 * 128;
        int tileSize = 128;
        int x = brushTilesheetPos[0];
        int y = brushTilesheetPos[1];
        for (y = 12; y >= 0; y--)
        {
            for (x = 0; x < 23; x++)
            {
                ImVec2 u0 = ImVec2((((float)x + 1) * (float)tileSize) / (float)sheetWidth, ((float)y * (float)tileSize) / (float)sheetHeight);
                ImVec2 u1 = ImVec2(((float)x * (float)tileSize) / (float)sheetWidth, (((float)y + 1) * (float)tileSize) / (float)sheetHeight);
                
                ImGui::PushID(x * 13 + y);
                if (ImGui::ImageButton((void*)(intptr_t)textures.GetTexture("tilemap")->GetTexID(), ImVec2(32, 32), u1, u0))
                {
                    brushTilesheetPos[0] = x;
                    brushTilesheetPos[1] = y;
                    if (painting)
                    {
//                        PaintSelectedTile();
                    }
                }
                ImGui::PopID();
                ImGui::SameLine();
            }
            ImGui::NewLine();
        }
    }
    ImGui::End();
}

void ToggleButton(const char* str_id, bool* v)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    
    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;
    
    if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
        *v = !*v;
    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = *v ? IM_COL32(145+20, 211, 68+20, 255) : IM_COL32(218-20, 218-20, 218-20, 255);
    else
        col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);
    
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
}

void GameLayer::BuildCurrentPaintbrush()
{
    ImGui::Begin("Selected Renderable");
    ImGui::Text("Currently selected %d, %d", brushTilesheetPos[0], brushTilesheetPos[1]);
    int sheetWidth = 23 * 128;
    int sheetHeight = 13 * 128;
    int tileSize = 128;
    int x = brushTilesheetPos[0];
    int y = brushTilesheetPos[1];
    
    ImVec2 u0 = ImVec2((((float)x + 1) * (float)tileSize) / (float)sheetWidth, ((float)y * (float)tileSize) / (float)sheetHeight);
    ImVec2 u1 = ImVec2(((float)x * (float)tileSize) / (float)sheetWidth, (((float)y + 1) * (float)tileSize) / (float)sheetHeight);
    
    ImGui::Image((void*)(intptr_t)textures.GetTexture("tilemap")->GetTexID(), ImVec2(64, 64), u1, u0);
    ImGui::Spacing();
    ImGui::Text("Painting");
    ImGui::SameLine();
    ToggleButton("Painting", &painting);
    ImGui::Text("Adding Layers");
    ImGui::SameLine();
    ToggleButton("AddLayer", &addingLayer);
    
    
    if (ImGui::Button("Save Map"))
    {
        SaveTilemap();
    }
    
    ImGui::End();
}


void GameLayer::BuildTileLayerSelector()
{
    int sheetWidth = 23 * 128;
    int sheetHeight = 13 * 128;
    int tileSize = 128;
    
    ImGui::Begin("Tile selection");
    
    if (selectedTile == nullptr)
    {
        ImGui::Text("No tile selected!");
        ImGui::End();
        return;
    }
    
    std::vector<Renderable2D*>* Children = nullptr;
    if (selectedTile->GetType() != RenderableType::Group)
    {
        Children = new std::vector<Renderable2D*>();
        Children->push_back(selectedTile);
    }
    else
    {
        Children = (std::vector<Renderable2D*>*)(((Group*)selectedTile)->GetChildren());
    }
    
    ImGui::Text("Group @ %d, %d", selectedTilesTilePos[0], selectedTilesTilePos[1]);
    
    for (int i = 0; i < Children->size(); i++)
    {
        if ((*Children)[i] == cursor) continue;
        
        ImGui::Text("Tile layer %d", i + 1);
        ImGui::SameLine();
        
        int x = (*Children)[i]->GetTilesheetPos().x;
        int y = (*Children)[i]->GetTilesheetPos().y;
        
        ImVec2 u0 = ImVec2((((float)x + 1) * (float)tileSize) / (float)sheetWidth, ((float)y * (float)tileSize) / (float)sheetHeight);
        ImVec2 u1 = ImVec2(((float)x * (float)tileSize) / (float)sheetWidth, (((float)y + 1) * (float)tileSize) / (float)sheetHeight);
        
        ImGui::PushID((x * GAMESPACE_Y * 2) + y);
        if (ImGui::ImageButton((void*)(intptr_t)textures.GetTexture("tilemap")->GetTexID(), ImVec2(64, 64), u1, u0))
        {
            selectedTile = (*Children)[i];
            
            if (painting)
            {
                PaintSelectedTile();
            }
        }
        ImGui::PopID();
        
    }
    ImGui::End();
}

void GameLayer::OnDraw()
{
    Render();
}

bool GameLayer::MouseScroll(MouseScrolledEvent& e)
{
    e.Handle();
    return false;
}

bool GameLayer::MouseMove(MouseMovedEvent& e)
{
    float mouseX, mouseY;
    float mouseXN = (float) e.getPos().x / (float) screenSize.x;
    float mouseYN = (float) e.getPos().y / (float) screenSize.y;

    if (mouseXN < 0.5f) { mouseX = -screenExtremes.x + screenExtremes.x * mouseXN * 2; }
    else { mouseX = screenExtremes.x * (mouseXN - 0.5f) * 2; }
    
    if (mouseYN < 0.5f) { mouseY = -screenExtremes.y + screenExtremes.y * mouseYN * 2; }
    else { mouseY = screenExtremes.y * ((mouseYN - 0.5f) * 2); }

    mousePos = Vec2f(mouseX, mouseY);

    return false;
}

void GameLayer::PaintMousedTile(bool force)
{
    ImGuiIO io = ImGui::GetIO();
    if (io.WantCaptureMouse)
    {
        return;
    }
    
    bool select = KevInput::IsMouseButtonPressed(MouseCode::ButtonLeft) || KevInput::IsMouseButtonPressed(MouseCode::ButtonRight);
    
    if (keyTimeout.getTimeMS() >= 500 && select)
    {
            keyTimeout.Reset();
            int x = (int)(mousePos.x + GAMESPACE_X);
            int y = (int)(mousePos.y + GAMESPACE_Y);
            if (abs(mousePos.x) > GAMESPACE_X)
            {//WARN: Unbracked if
                if (mousePos.x < 0)
                    x++;
                else
                    x--;
            }
            else if (abs(mousePos.y) > GAMESPACE_Y)
            {//WARN: Unbracked if
                if (mousePos.y < 0)
                    y++;
                else
                    y--;
            }
        if (cursor != nullptr && cursor->GetParent() != nullptr)
        {
            ((Group*)cursor->GetParent())->Delete(cursor);
        }

        brushPos.x = x;
        brushPos.y = y;
        selectedTile = tilemap[x][y];
            
        if (select || force)
        {
            
            if(selectedTile->GetType() == RenderableType::Group)
            {
                std::vector<Renderable2D*>* children = (std::vector<Renderable2D*>*)((Group*)selectedTile)->GetChildren();
                if (children->size() > 1)
                {
                    ((Group*)selectedTile)->Add(cursor);
                    return;
                }
                else
                {
                    selectedTile = (*children)[0];
                }
            }
            
            if (tilemap[x][y] != nullptr)
            {
                tilemap[x][y]->Add(cursor);
            }

            if (painting && KevInput::IsMouseButtonPressed(MouseCode::ButtonLeft))
            {
                PaintSelectedTile();
            }
        }
        
    }
}


void GameLayer::PaintSelectedTile()
{
    if(selectedTile->GetType() == RenderableType::Group)
    {
        std::vector<Renderable2D*>* children = (std::vector<Renderable2D*>*)((Group*)selectedTile)->GetChildren();
        if (children->size() > 1)
        {
            return;
        }
        else
        {
            selectedTile = (*children)[0];
        }
    }
    
    if (selectedTile->GetTilesheetPos().x != brushTilesheetPos[0] || selectedTile->GetTilesheetPos().y != brushTilesheetPos[1])
    {
        if (undoCache.size() > 99)
        {
            for (int i = 1; i < 99; i++)
            {
                undoCache[i-1] = undoCache[i];
            }
            undoCache[99] = Move(selectedTile, selectedTile->GetTilesheetPos());
        }
        else
        {
            undoCache.push_back(Move(selectedTile, selectedTile->GetTilesheetPos()));
        }
        
        selectedTile->SetTilesheetPos(brushTilesheetPos[0], brushTilesheetPos[1]);
    }
}

bool GameLayer::MouseButton(MouseButtonPressedEvent& e)
{
    if (e.getButton() == MouseCode::ButtonLeft)
    {
        PaintMousedTile(true);
    }
    if (e.getButton() == MouseCode::ButtonRight)
    {
        if(selectedTile->GetType() == RenderableType::Group)
        {
            ((Group*)selectedTile)->Add(new Sprite(0, 0, 1, 1, textures.GetTexture("tilemap"), Vec2u(brushTilesheetPos[0], brushTilesheetPos[1])));
        }
        else if (selectedTile->GetParent() != nullptr)
        {
            Group* par = ((Group*)selectedTile->GetParent());
            par->Add(new Sprite(0, 0, 1, 1, textures.GetTexture("tilemap"), Vec2u(brushTilesheetPos[0], brushTilesheetPos[1])));
        }
    }
    return false;
}

bool GameLayer::WindowResize(WindowResizeEvent& e)
{
    screenSize = e.getScreenSize();
    return false;
}

bool GameLayer::KeyDown(KeyPressedEvent& e)
{
    if (keyDebounce.GetTimePassed() < keyDebounceInterval)
    {
        return false;
    }
    keyDebounce.Reset();

    KeyCode key = (KeyCode)(e.GetKeyCode());

    switch (key)
    {
        case(KEV_KEY_F3):
        {
            SetImGuiEnabled(!IsImGuiEnabled());
            break;
        }

        case(KEV_KEY_F11):
        {
            if (parent != nullptr) 
            {

                parent->ToggleFullscreen();
            }
            break;
        }

        case(KEV_KEY_F1):
        {
            if (parent->IsVSync())
            {
                LOG_INF("Turning VSync off\n");
                parent->SetVSync(0);
            }
            else
            {
                LOG_INF("Turning VSync on\n");
                parent->SetVSync(1);
            }
            break;
        }

        case(KEV_KEY_P):
        {
            paused = !paused;
            LOG_INF("Game ");
            if (paused)
            {
                printf("unpaused\n");
            }
            else
            {
                printf("paused\n");
            }
            break;
        }
            
        case(KEV_KEY_C):
        {
            if (selectedTile != nullptr)
            {
                copiedTilePos[0] = selectedTile->GetTilesheetPos().x;
                copiedTilePos[1] = selectedTile->GetTilesheetPos().y;
            }
            break;
        }
        case(KEV_KEY_V):
        {
            if (selectedTile != nullptr && KevInput::IsKeyPressed(KeyCode::LeftControl))
            {
                selectedTile->SetTilesheetPos(copiedTilePos[0], copiedTilePos[1]);
            }
            break;
        }
        
        case(KEV_KEY_Z):
        {
            if (undoCache.size() > 0 && KevInput::IsKeyPressed(KeyCode::LeftControl))
            {
                LOG_INF("Undo\n");
                Move undo = undoCache[undoCache.size() - 1];
                undo.renderable->SetTilesheetPos(undo.oldTile.x, undo.oldTile.y);
                undoCache.pop_back();
            }
            break;
        }
        case(KEV_KEY_DELETE):
        {
            LOG_INF("Delete tile\n");
            if (selectedTile != nullptr && selectedTile->GetParent() != nullptr)
            {
                if (selectedTile->GetType() == RenderableType::Group)
                {
                    std::vector<Renderable2D*>* rend = (std::vector<Renderable2D*>*)selectedTile->GetChildren();
                    rend->clear();
                }
                else if (selectedTile->GetParent()->GetType() == RenderableType::Group)
                {
                    LOG_INF("Removing from dad\n");
                    Group* par = ((Group*)selectedTile->GetParent());
                    par->Delete(selectedTile);
                    selectedTile = par;
                }
            }
            break;
        }
            
        case(KEV_KEY_B):
        {
            painting = !painting;
            break;
        }
            

        default:
            break;
    }

    return true;
}

void GameLayer::OnEvent(Event& e)
{
    EventDispatcher dispatch(e);
    dispatch.Dispatch<MouseMovedEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseMove));
    dispatch.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(GameLayer::WindowResize));
    dispatch.Dispatch<MouseScrolledEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseScroll));
    dispatch.Dispatch<KeyPressedEvent>(KEV_BIND_EVENT_FN(GameLayer::KeyDown));
    dispatch.Dispatch<MouseButtonPressedEvent>(KEV_BIND_EVENT_FN(GameLayer::MouseButton));

    camera.OnEvent(e);

}

void GameLayer::SaveTilemap()
{
    
}
