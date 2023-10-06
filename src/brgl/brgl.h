#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

namespace br
{
    std::string OpenTextFile(const char* _filePath);
}

namespace br::gl
{
    enum class Status
    {
        ERROR = 0,
        ERROR_WINDOW_CREATION, ERROR_GLCONTEXT_INIT, ERROR_GLEW_INIT,
        ERROR_SHADER_COMPILATION,
        OK
    };

    const Status CreateWindowContext(SDL_Window*& _window, const char* _windowName, const int& _windowWidth, const int& _windowHeight);

    class ShaderProgram
    {
    public:
        void AddShader(const GLuint& _shaderID);
        const GLuint CompileShader(const GLenum& _shaderType, const char* _source);
        const Status Link();
        const GLuint GetID() { return shaderProgramID; }
        const bool IsLinked() { return isLinked; }

    private:
        GLuint shaderProgramID;
        std::vector<GLuint> shaderObjects;
        bool isLinked;

    public:
        ShaderProgram();
        ~ShaderProgram();
    };

    const Status CompileShader(GLuint& _shaderID, const GLenum& _shaderType, const char* _source);
    std::string GetShaderStatus(const GLuint& _shaderID);
    std::string GetProgramStatus(const GLuint& _programID);
}