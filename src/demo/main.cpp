#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

#include "brgl/brgl.h"

int ThrowSDLError()
{
    std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return ThrowSDLError();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window*  sdlWindow = SDL_CreateWindow("Demo Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (sdlWindow == nullptr)
        return ThrowSDLError();   

    SDL_GLContext sdlGLContext = SDL_GL_CreateContext(sdlWindow);
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        std::cout << "GLEW Error: " << glewGetErrorString(glewStatus) << std::endl;
        return 1;
    }
    std::cout << "GLEW: " << "OK" << std::endl;

    bool runtime = true;
    SDL_Event sdlEvent;
    while (runtime)
    {
        while (SDL_PollEvent(&sdlEvent))
        {
            switch (sdlEvent.type)
            {
                case SDL_QUIT:
                    runtime = false;
                    break;
            }
        }
        glClearColor(1.0f ,0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(sdlWindow);
    }

    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();

    return 0;
}