#include "KevEngine.h"
#include "EntryPoint.h"

unsigned int Renderable2D::globalNumRenderables;

KevEngine* KevEngine::curEngine = nullptr;

extern KevEngine* CreateApplication();

unsigned int KevEngine::LastFrameKeep = 0;
unsigned int KevEngine::LastUpdateKeep = 0;

KevEngine::KevEngine(KevEngine* child)
    : childInstance(child)
{
    LOG_INF("Making engine instance\n");
    if (curEngine != nullptr)
    {
        LOG_ERR("Engine already exists!!\n");
    }
    curEngine = this;
    m_Window = Window::Create(WindowInfo());
	m_Window->SetEventCallback(KEV_BIND_EVENT_FN(KevEngine::OnEvent));

    imGuiLayer = ImGuiLayer::Create(m_Window);
    PushOverlay(imGuiLayer);
    
    fps.Start();
    ups.Start();
}

KevEngine::~KevEngine()
{
    for (int i = 0; i < EngLayerStack.GetSize(); i++)
    {
        if (EngLayerStack[i] == imGuiLayer)
        {
            continue;
        }
        delete EngLayerStack[i];
    }
    
//    delete childInstance;
}

void KevEngine::EngineSwap()
{
    if (curEngine == nullptr)
    {
        return;
    }
    
    delete curEngine;
    curEngine = CreateApplication();
}

bool KevEngine::OnWindowClose(WindowCloseEvent& e)
{
    running = false;
    return true;
}

bool KevEngine::OnWindowResize(WindowResizeEvent& e)
{
    if (e.getScreenSize().x == 0 || e.getScreenSize().y == 0)
	{
		minimized = true;
		return false;
	}

    m_Window->SetView(e.getScreenSize().x, e.getScreenSize().y);
    return false;
}


void KevEngine::OnImGuiRender()
{
    imGuiLayer->Begin();
    for (Layer* layer : EngLayerStack)
    {
        layer->OnImGuiRender();
    }  
    imGuiLayer->End();
}

void KevEngine::OnUpdate()
{
    unsigned int newUpdate = ups.FrameKeep();
    if ( newUpdate != 0)
    {
        LastUpdateKeep = newUpdate;
    }
    
    for (Layer* layer : EngLayerStack)
    {
        layer->OnUpdate();
    }


    if (childInstance != nullptr)
    {
        childInstance->OnGameUpdate();
    }
}

void KevEngine::OnDraw()
{
    unsigned int newFrames = fps.FrameKeep();
    if ( newFrames != 0)
    {
        LastFrameKeep = newFrames;
    }
    
    for (Layer* layer : EngLayerStack)
    {
        layer->OnDraw();
    }
    if (childInstance != nullptr)
    {
        childInstance->OnGameDraw();
    }
}

void KevEngine::OnEvent(Event& e)
{

    EventDispatcher dispatch(e);
    dispatch.Dispatch<WindowCloseEvent>(KEV_BIND_EVENT_FN(KevEngine::OnWindowClose));
    dispatch.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(KevEngine::OnWindowResize));
    

    for (auto layer = EngLayerStack.rbegin(); layer != EngLayerStack.rend(); ++layer)
    {
        if (!e.IsHandled())
        {
            (*layer)->OnEvent(e);
        }
    }

    if (!e.IsHandled())
    {
        e.Handle();
    }
}

void KevEngine::PushLayer(Layer* layer)
{
    EngLayerStack.PushLayer(layer);
    layer->OnAttach();
}

void KevEngine::PushOverlay(Layer* layer)
{
    EngLayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void KevEngine::Run()
{
    double c = 1.0f / 120.0f;
    unsigned int updatesThiscSec = 0;
    timer.Reset();
    while (running)
    {
        if (!minimized)
        {
            if (updatesThiscSec < c || m_Window->IsVSync())
            {
                OnUpdate();
                updatesThiscSec++;
            }
            else if (timer.GetTimePassed() >= c)
            {
                updatesThiscSec = 0;
                timer.Reset();
            }
            OnDraw();
            OnImGuiRender();
        }

        m_Window->OnUpdate();
    }
}
