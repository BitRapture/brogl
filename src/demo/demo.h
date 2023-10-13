#pragma once
#include "brgl/brgl.h"

namespace br
{

    class DemoApplication
    {
    public:
        void Run();

    private:
        void Initialize();
        void ResizeViewport();

    private:
        gl::Status initStatus;
        SDL_Window* sdlWindow;

    public:
        DemoApplication() :
            sdlWindow{ nullptr }
        {
            Initialize();
        }
        ~DemoApplication();
    };

}