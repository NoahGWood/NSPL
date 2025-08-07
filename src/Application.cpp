#include <nspl/Application.hpp>
#include <nspl/event/Event.h>
#include <nspl/common/Logger.h>

volatile std::sig_atomic_t g_SignalCaught = 0;

void SignalHandler(int signal){
    if(signal == SIGINT){
        g_SignalCaught = 1;
    }
}


namespace NSPL
{
    bool Application::Init(const WindowDesc& desc){
        std::signal(SIGINT, SignalHandler);
        m_Running = true;
        // Setup Logging
        Logger::Init();
        // Create main window
        auto main = std::make_unique<Window>(desc);
        m_Windows[main->GetWindowID()] = std::move(main);
        return m_Running;
    }
    void Application::Run(){
        m_Running = true;
        while(m_Running && !g_SignalCaught){
            PollEvents();
        }
    }
    void Application::Shutdown(){
        m_Running = false;
    }
    // void Application::OnEvent(const NSPL::Event& event){ }
    void Application::Quit(){
        Shutdown();
    }

    // --- Event Subscriptions ---
    int Application::SubscribeUpdate(const gofpp::Observable<UpdateEvent>::Handler& handler){
        return m_Updates.subscribe(handler);
    }

    void Application::UnsubscribeUpdate(int id){
        m_Updates.unsubscribe(id);
    }

    int Application::SubscribeEvent(const gofpp::Observable<Event>::Handler& handler) {
        return m_Events.subscribe(handler);
    }

    void Application::UnsubscribeEvent(int id) {
        m_Events.unsubscribe(id);
    }

    void Application::OnUpdate(float deltaTime){
        m_Updates.notify(deltaTime);
    }

    void Application::OnEvent(const Event& event){
        m_Events.notify(event);
    }

    void Application::PollEvents(){
        SDL_Event sdlEvent;
        while(SDL_PollEvent(&sdlEvent)){
            std::unique_ptr<Event> ev;
            switch(sdlEvent.type){
                case SDL_QUIT:{
                    QuitEvent ev;
                    m_Events.notify(ev);
                    Quit();
                    break;
                }
                case SDL_KEYDOWN:{
                    KeyDownEvent ev;
                    ev.keycode = sdlEvent.key.keysym.sym;
                    ev.repeat = sdlEvent.key.repeat != 0;
                    m_Events.notify(ev);
                    break;
                }
                case SDL_MOUSEMOTION:{
                    MouseMoveEvent ev;
                    ev.x = sdlEvent.motion.x;
                    ev.y = sdlEvent.motion.y;
                    ev.dx = sdlEvent.motion.xrel;
                    ev.dy = sdlEvent.motion.yrel;
                    m_Events.notify(ev);
                    break;
                }

                // ...handle other SDL events...

                default:
                    continue; // skip unhandled events
            }
        }
    }
} // namespace NSPL
