#pragma once
#include <string>

namespace NSPL
{
    struct WindowDesc{
        std::string title = "NSPL Window";
        int width = 1280;
        int height = 720;
        bool resizable = true;
        bool fullscreen = false;
        bool vsync = true;
    };
} // namespace NSPL
