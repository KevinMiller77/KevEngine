#include "KevEngine.h"
#include "EntryPoint.h"

KevEngine* KevEngine::curEngine = nullptr;

KevEngine::KevEngine()
{
    LOG_INF("Making engine instance\n");
    if (curEngine != nullptr)
    {
        LOG_ERR("Engine already exists!!\n");
    }
    curEngine = this;
	LOG_INF("Creating window\n");
    window = Window::Create(WindowInfo());
    LOG_INF("Window made\n");
	window->SetEventCallback(KEV_BIND_EVENT_FN(KevEngine::OnEvent));
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

    minimized = false;
    return false;
}

void KevEngine::OnUpdate()
{
    for (Layer* layer : layers)
    {
        layer->OnUpdate();
        layer->OnDraw();
    }
}

void KevEngine::OnEvent(Event& e)
{

    EventDispatcher dispatch(e);
    dispatch.Dispatch<WindowCloseEvent>(KEV_BIND_EVENT_FN(KevEngine::OnWindowClose));
    dispatch.Dispatch<WindowResizeEvent>(KEV_BIND_EVENT_FN(KevEngine::OnWindowResize));

    for (Layer* layer: layers)
    {
        if (!e.IsHandled())
        {
            layer->OnEvent(e);
        }
    }

    if (!e.IsHandled())
    {
        e.Handle();
    }
}

void KevEngine::PushLayer(Layer* layer)
{
    layers.insert(layers.begin(), layer);
    layer->OnAttach();
}

void KevEngine::PushOverlay(Layer* layer)
{
    layers.push_back(layer);
    layer->OnAttach();
}

void KevEngine::Run()
{
    while (running)
    {
        if (!minimized)
        {
            OnUpdate();
        }

        window->OnUpdate();
    }
}
