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
    
    guideGrids = new Group(Mat4f::translation(Vec3f(-screenExtremes.x, -screenExtremes.y, 0.0f)));
    scene = new Group(Mat4f::translation(Vec3f(-screenExtremes.x, -screenExtremes.y, 0.0f)));
    
    for (float x = 0; x < GAMESPACE_X * 2; x += 1)
    {
        for (float y = 0; y < GAMESPACE_Y * 2; y += 1)
        {
            if (x == 0)
            {
                guideGrids->Add(new Sprite(0, y - 0.025, GAMESPACE_X * 2, 0.05f, Vec4f(1.0f, 1.0f, 1.0f, 0.4f)));
            }
            if (y == 0)
            {
                guideGrids->Add(new Sprite(x - 0.025, 0, 0.05f, GAMESPACE_Y * 2, Vec4f(1.0f, 1.0f, 1.0f, 0.4f)));
            }

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
    Add(guideGrids);

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
        Manager.MouseCheck(mousePos, camera.GetWorldPos(GAMESPACE_X * 2, GAMESPACE_Y * 2));
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
                }
                if (ImGui::IsItemHovered())
                {
                    LOG_INF("Hovering over %d, %d\n", x, y);
                    if (KevInput::IsKeyPressed(KEV_KEY_1)) hotbarItems[0] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_2)) hotbarItems[1] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_3)) hotbarItems[2] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_4)) hotbarItems[3] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_5)) hotbarItems[4] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_6)) hotbarItems[5] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_7)) hotbarItems[6] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_8)) hotbarItems[7] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_9)) hotbarItems[8] = Vec2u(x, y);
                    else if (KevInput::IsKeyPressed(KEV_KEY_0)) hotbarItems[9] = Vec2u(x, y);
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
    ImGui::Begin("Paintbrush selection");
    ImGui::Text("Current Tile %d, %d", brushTilesheetPos[0], brushTilesheetPos[1]);
    int sheetWidth = 23 * 128;
    int sheetHeight = 13 * 128;
    int tileSize = 128;
    int x = brushTilesheetPos[0];
    int y = brushTilesheetPos[1];
    
    ImVec2 u0 = ImVec2((((float)x + 1) * (float)tileSize) / (float)sheetWidth, ((float)y * (float)tileSize) / (float)sheetHeight);
    ImVec2 u1 = ImVec2(((float)x * (float)tileSize) / (float)sheetWidth, (((float)y + 1) * (float)tileSize) / (float)sheetHeight);
    
    ImGui::Image((void*)(intptr_t)textures.GetTexture("tilemap")->GetTexID(), ImVec2(64, 64), u1, u0);
    ImGui::Spacing();
    ImGui::Text("Hotbar");
    ImGui::Spacing();
    
    for (int i = 0; i < 10; i++)
    {
        x = hotbarItems[i].x;
        y = hotbarItems[i].y;
        
        u0 = ImVec2((((float)x + 1) * (float)tileSize) / (float)sheetWidth, ((float)y * (float)tileSize) / (float)sheetHeight);
        u1 = ImVec2(((float)x * (float)tileSize) / (float)sheetWidth, (((float)y + 1) * (float)tileSize) / (float)sheetHeight);
        ImGui::Image((void*)(intptr_t)textures.GetTexture("tilemap")->GetTexID(), ImVec2(24, 24), u1, u0);
        ImGui::SameLine();
    }
    ImGui::NewLine();
    for (int i = 1; i < 11; i++)
    {
        x = i < 10 ? i : 0;
        y = 0;
        
        u0 = ImVec2((((float)x + 1) * (float)tileSize) / (float)sheetWidth, ((float)y * (float)tileSize) / (float)sheetHeight);
        u1 = ImVec2(((float)x * (float)tileSize) / (float)sheetWidth, (((float)y + 1) * (float)tileSize) / (float)sheetHeight);
        
        ImGui::Image((void*)(intptr_t)textures.GetTexture("tilemap")->GetTexID(), ImVec2(24, 24), u1, u0);
        ImGui::SameLine();
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
    
    ImGui::Text("Group @ %f, %f", GetTopLevelParent(selectedTile)->GetPosition().x, GetTopLevelParent(selectedTile)->GetPosition().y);
    
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
            
            if (brushMode == BrushFunction::PAINT)
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
    // const int scale = e.getYOffset();
    // LOG_INF("Zoom %d", scale);
    // camera.SetZoomLevel(camera.GetZoomLevel() + ((float)scale * 0.1f));
    
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
            Vec2f camOff = camera.GetWorldPos(GAMESPACE_X * 2, GAMESPACE_Y * 2);

            int x = (int)(mousePos.x + camOff.x + GAMESPACE_X);
            int y = (int)(mousePos.y - camOff.y + GAMESPACE_Y);
            if (abs(mousePos.x + camOff.x) > GAMESPACE_X)
            {//WARN: Unbracked if
                if (mousePos.x + camOff.x < 0)
                    x = 0;
                else
                    x = (int)(GAMESPACE_X * 2) - 1;
            }
            else if (abs(mousePos.y - camOff.y) > GAMESPACE_Y)
            {//WARN: Unbracked if
                if (mousePos.y - camOff.y < 0)
                    y = 0;
                else
                    y = (int)(GAMESPACE_Y * 2) - 1;
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
                    if (children->size() == 0)
                    {

                    }
                    else
                    {
                        selectedTile = (*children)[0];
                    }
                }
            }
            
            if (tilemap[x][y] != nullptr)
            {
                tilemap[x][y]->Add(cursor);
            }

            if (brushMode == BrushFunction::PAINT && KevInput::IsMouseButtonPressed(MouseCode::ButtonLeft))
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
        case(KEV_KEY_1):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[0].x == 22 && hotbarItems[0].y == 12)) break; brushTilesheetPos = hotbarItems[0]; break; }
        case(KEV_KEY_2):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[1].x == 22 && hotbarItems[1].y == 12)) break; brushTilesheetPos = hotbarItems[1]; break; }
        case(KEV_KEY_3):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[2].x == 22 && hotbarItems[2].y == 12)) break; brushTilesheetPos = hotbarItems[2]; break; }
        case(KEV_KEY_4):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[3].x == 22 && hotbarItems[3].y == 12)) break; brushTilesheetPos = hotbarItems[3]; break; }
        case(KEV_KEY_5):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[4].x == 22 && hotbarItems[4].y == 12)) break; brushTilesheetPos = hotbarItems[4]; break; }
        case(KEV_KEY_6):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[5].x == 22 && hotbarItems[5].y == 12)) break; brushTilesheetPos = hotbarItems[5]; break; }
        case(KEV_KEY_7):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[6].x == 22 && hotbarItems[6].y == 12)) break; brushTilesheetPos = hotbarItems[6]; break; }
        case(KEV_KEY_8):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[7].x == 22 && hotbarItems[7].y == 12)) break; brushTilesheetPos = hotbarItems[7]; break; }
        case(KEV_KEY_9):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[8].x == 22 && hotbarItems[8].y == 12)) break; brushTilesheetPos = hotbarItems[8]; break; }
        case(KEV_KEY_0):{ ImGuiIO io = ImGui::GetIO(); if(io.WantCaptureMouse || (hotbarItems[9].x == 22 && hotbarItems[9].y == 12)) break; brushTilesheetPos = hotbarItems[9]; break; }
            
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

        case(KEV_KEY_G):
        {
            if (guideGrids->IsEnabled())
            {
                guideGrids->Disable();
            }
            else
            {
                guideGrids->Enable();
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
            if (KevInput::IsKeyPressed(KeyCode::LeftControl))
            {
                if (selectedTile != nullptr)
                {
                    copiedTilePos[0] = selectedTile->GetTilesheetPos().x;
                    copiedTilePos[1] = selectedTile->GetTilesheetPos().y;
                }
            }
            break;
        }
        case(KEV_KEY_V):
        {
            if (KevInput::IsKeyPressed(KeyCode::LeftControl))
            {
                if (selectedTile != nullptr && KevInput::IsKeyPressed(KeyCode::LeftControl))
                {
                    selectedTile->SetTilesheetPos(copiedTilePos[0], copiedTilePos[1]);
                }
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
            if ((int)brushMode == 3)
            {
                brushMode = (BrushFunction)(0);
            }
            else
            {
                brushMode = (BrushFunction)((int)brushMode + 1);
            }
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
