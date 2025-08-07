#pragma once
#include <string>
#include <utility>
#include <nspl/window/WindowDesc.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

namespace NSPL
{
    class Window{
        public:
            Window(const WindowDesc& desc);
            ~Window();

            void SetTitle(const std::string& title);
            void Resize(int w, int h);
            void ToggleFullscreen();

            // Getters
            std::pair<int,int> GetSize() const;
            void* GetNativeWindowHandle() const;
            void* GetNativeDisplayType() const;
            const int GetWindowID() const { return m_WindowID; }
            const bool GetFullscreen() const { return m_Fullscreen; }

            // Disallow copy but allow move
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;
            Window(Window&& other) noexcept;
            Window& operator=(Window&& other) noexcept;

        private:
            SDL_Window* m_SDLWindow = nullptr;
            SDL_SysWMinfo m_PlatformInfo;
            int m_WindowID = 0;
            bool m_Fullscreen = false;

            void UpdateFullscreenState();
    };
} // namespace NSPL
