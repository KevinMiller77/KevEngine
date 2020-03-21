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
    LOG_INF("LAy on\n");
    for (int i = 0; i < LayerStack.GetSize(); i++)
    {
        ("LAY DOO\n");
        LayerStack[i]->OnUpdate();
        ("LAY DONE\n");
    }

    LOG_INF("LAy off\n");

    if (childInstance != nullptr)
    {
        childInstance->OnChildUpdate();
    }
    LOG_INF("Done\n");
}

void KevEngine::OnDraw()
{
    for (Layer* layer : LayerStack)
    {
        LOG_INF("Drawing layer\n");
        layer->OnDraw();
        LOG_INF("Drew layer\n");
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
                LOG_INF("UPDATED\n");
                updatesThiscSec++;
            }
            else if (timer.GetTimePassed() >= c)
            {
                updatesThiscSec = 0;
                timer.Reset();
            }
            OnImGuiRender();
            LOG_INF("GUI\n");
            OnDraw();
            LOG_INF("DREW\n");
        }

        LOG_INF("B4\n");
        window->OnUpdate();
        LOG_INF("A4\n");
    }
}
