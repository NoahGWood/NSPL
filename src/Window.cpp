#include <nspl/window/Window.hpp>
#include <stddef.h>

namespace NSPL
{
    Window::Window(const WindowDesc& desc){
        uint32_t flags = SDL_WINDOW_SHOWN;
        if (desc.resizable) flags |= SDL_WINDOW_RESIZABLE;
        if (desc.fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

        m_SDLWindow = SDL_CreateWindow(
            desc.title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            desc.width, desc.height,
            flags
        );

        if(!m_SDLWindow){
            // throw std::runtime_error("Failed to create SDL_Window!");
            return;
        }
        SDL_VERSION(&m_PlatformInfo.version);
        if(!SDL_GetWindowWMInfo(m_SDLWindow, &m_PlatformInfo)){
        //     // TODO
            return;
        }

        m_WindowID = SDL_GetWindowID(m_SDLWindow);
        m_Fullscreen = desc.fullscreen;
    }

    Window::~Window(){
        if(m_SDLWindow){
            SDL_DestroyWindow(m_SDLWindow);
            m_SDLWindow = nullptr;
        }
    }

    void Window::SetTitle(const std::string& title){
        if(m_SDLWindow){
            SDL_SetWindowTitle(m_SDLWindow, title.c_str());
        }
    }
    void Window::Resize(int width, int height) {
        if (m_SDLWindow) {
            SDL_SetWindowSize(m_SDLWindow, width, height);
        }
    }

    void Window::ToggleFullscreen() {
        if (!m_SDLWindow) return;

        m_Fullscreen = !m_Fullscreen;
        UpdateFullscreenState();
    }

    void Window::UpdateFullscreenState() {
        if (!m_SDLWindow) return;

        if (m_Fullscreen) {
            SDL_SetWindowFullscreen(m_SDLWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        } else {
            SDL_SetWindowFullscreen(m_SDLWindow, 0);
        }
    }

    std::pair<int, int> Window::GetSize() const {
        int w = 0, h = 0;
        if (m_SDLWindow) {
            SDL_GetWindowSize(m_SDLWindow, &w, &h);
        }
        return {w, h};
    }

    void* Window::GetNativeWindowHandle() const {
        return m_SDLWindow;
    }

    Window::Window(Window&& other) noexcept {
        m_SDLWindow = other.m_SDLWindow;
        m_WindowID = other.m_WindowID;
        m_Fullscreen = other.m_Fullscreen;
        other.m_SDLWindow = nullptr;
    }

    Window& Window::operator=(Window&& other) noexcept {
        if (this != &other) {
            if (m_SDLWindow) SDL_DestroyWindow(m_SDLWindow);
            m_SDLWindow = other.m_SDLWindow;
            m_WindowID = other.m_WindowID;
            m_Fullscreen = other.m_Fullscreen;
            other.m_SDLWindow = nullptr;
        }
        return *this;
    }
    
    void* Window::GetNativeDisplayType() const {
        return (void*)&m_PlatformInfo.info.x11.display;
    }

} // namespace NSPL
