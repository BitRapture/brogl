#include "demo.h"
#include <iostream>
#include <cmath>

namespace br
{

    void DemoApplication::Run()
    {
        if (initStatus != gl::Status::OK)
            return;

        gl::ShaderProgram shaderProgram;
        GLuint vertShader = shaderProgram.CompileShader(
            GL_VERTEX_SHADER,
            OpenTextFile("./shader.vert").c_str()
        );
        GLuint fragShader = shaderProgram.CompileShader(
            GL_FRAGMENT_SHADER,
            OpenTextFile("./shader.frag").c_str()
        );
        if (shaderProgram.Link() != gl::Status::OK)
        {
            std::cout << gl::GetShaderStatus(vertShader) << std::endl;
            return;
        }

        gl::Quad quad(-0.5f, -0.5f, 1.0f, 1.0f);

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
                    case SDL_KEYUP:
                        ResizeViewport();
                        break;
                }
            }

            glClearColor(0.75f, 0.05f, 0.95f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram.GetID());
            quad.Draw();

            SDL_GL_SwapWindow(sdlWindow);
        }
    }

    void DemoApplication::ResizeViewport()
    {
        int width, height;
        SDL_GetWindowSize(sdlWindow, &width, &height);
        glViewport(0, 0, width, height);
    }

    void DemoApplication::Initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            initStatus = gl::Status::ERROR;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        initStatus = br::gl::CreateWindowContext(sdlWindow, glContext, "Demo Window", 1280, 720);
    }

    DemoApplication::~DemoApplication()
    {
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
    }
}