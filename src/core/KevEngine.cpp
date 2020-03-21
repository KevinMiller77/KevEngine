#include "KevEngine.h"
#include "EntryPoint.h"

KevEngine* KevEngine::curEngine = nullptr;

KevEngine::KevEngine(KevEngine* child)
    : childInstance(child)
{
    LOG_INF("Making engine instance\n");
    if (curEngine != nullptr)
    {
        LOG_ERR("Engine already exists!!\n");
    }
    curEngine = this;
    window = Window::Create(WindowInfo());
	window->SetEventCallback(KEV_BIND_EVENT_FN(KevEngine::OnEvent));

    imGuiLayer = new ImGuiLayer();
    PushOverlay(imGuiLayer);
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

    window->SetView(e.getScreenSize().x, e.getScreenSize().y);
    return false;
}


void KevEngine::OnImGuiRender()
{
    imGuiLayer->Begin();
    for (Layer* layer : LayerStack)
    {
        layer->OnImGuiRender();
    }  
    imGuiLayer->End();
}

void KevEngine::OnUpdate()
{
    for (Layer* layer : LayerStack)
    {
        layer->OnUpdate();
    }


    if (childInstance != nullptr)
    {
        childInstance->OnChildUpdate();
    }
}

void KevEngine::OnDraw()
{
    for (Layer* layer : LayerStack)
    {
        layer->OnDraw();
    }
    if (childInstance != nullptr)
    {
        childInstance->OnChildDraw();
    }
}

void KevEngine::OnEvent(Event& e)
{

    EventDispatcher dispatch(e);
    dispatch.Dispatch<WindowCloseEvent>(KEV_BIND_EVENT_FN(KevEngine::OnWindowClose));
    dispatch.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(KevEngine::OnWindowResize));

    for (auto layer = LayerStack.rbegin(); layer != LayerStack.rend(); ++layer)
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
    LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void KevEngine::PushOverlay(Layer* layer)
{
    LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void KevEngine::Run()
{
    double c = 1.0f / 60.0f;
    unsigned int updatesThiscSec = 0;
    timer.Reset();
    while (running)
    {
        if (!minimized)
        {
            if (updatesThiscSec < 1)
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

        window->OnUpdate();
    }
}
