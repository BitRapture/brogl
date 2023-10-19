#include "demo.h"
#include <iostream>
#include <cmath>

namespace br
{

    void DemoApplication::Run()
    {
        if (initStatus != gl::Status::OK)
            return;

        gl::BufferObject<float> triangleVBO({
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        }, GL_FLOAT);

        gl::VertexArrayObject triangleVAO;
        triangleVAO.LinkBufferObject<float>(triangleVBO, 3);

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
            std::cout << gl::GetShaderStatus(vertShader) << std::endl;

        GLint colorUniform = shaderProgram["triangleColor"];
        float r, g, b;
        
        ResizeViewport();

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

            r += 0.001f;
            if (r > 1.0f) r = 0.0f;
            g = std::sin(r * 3.141f);
            b = std::cos(r * 3.141f);

            glClearColor(0.75f, 0.05f, 0.95f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram.GetID());
            glUniform4f(colorUniform, r, g, b, 1.0f);
            
            glBindVertexArray(triangleVAO.GetID());
            glDrawArrays(GL_TRIANGLES, 0, 3);

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