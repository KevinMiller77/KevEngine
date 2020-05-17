#include "MetalImGuiLayer.h"


MetalImGuiLayer::MetalImGuiLayer(Window* Parent)
    : ImGuiLayer(Parent)
{
}

void MetalImGuiLayer::OnAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigDockingWithShift = true;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    
    ImGui_ImplGlfw_InitForOpenGL(GET_GLFW_METAL_WINDOW(), true);
    ImGui_ImplMetal_Init(GET_METAL_DEVICE());
    
    RPD = [MTLRenderPassDescriptor new];
        
}

void MetalImGuiLayer::OnDetach()
{
    ImGui_ImplMetal_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void MetalImGuiLayer::Begin()
{
//    int width, height;
//    glfwGetFramebufferSize(GET_GLFW_METAL_WINDOW(), &width, &height);
//    layer.drawableSize = CGSizeMake(width, height);
    drawable = [GET_METAL_LAYER() nextDrawable];
    
    if (drawable == nil)
    {
        return;
    }
    
    RPD.colorAttachments[0].clearColor = MTLClearColorMake(1, 1, 1, 1);
    RPD.colorAttachments[0].texture = drawable.texture;
    RPD.colorAttachments[0].loadAction = MTLLoadActionClear;
    RPD.colorAttachments[0].storeAction = MTLStoreActionStore;
    
    CB = [GET_METAL_QUEUE() commandBuffer];
    
    RE = [CB renderCommandEncoderWithDescriptor:RPD];
    [RE pushDebugGroup:@"ImGui wind"];
    
    ImGui_ImplMetal_NewFrame(RPD);
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ShowDockSpace();
}

void MetalImGuiLayer::End()
{
    
    if (drawable == nil)
    {
        return;
    }
    
    ImGuiIO& io = ImGui::GetIO();
    KevEngine* app = KevEngine::Get();
    io.DisplaySize = ImVec2((float)app->GetWindow()->GetWidth(), (float)app->GetWindow()->GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), CB, RE);
    [RE popDebugGroup];
    [RE endEncoding];
    
    [CB presentDrawable:drawable];
    [CB commit];
    
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}


void MetalImGuiLayer::ShowDockSpace()
{
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    dockspace_flags |= ImGuiDockNodeFlags_NoDockingInCentralNode;
    dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
    // dockspace_flags |= ImGuiDockNodeFlags_AutoHideTabBar;

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &DockspaceEnabled, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}
