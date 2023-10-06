#include "brgl.h"

#include <fstream>

namespace br
{
    std::string OpenTextFile(const char* _filePath)
    {
        std::ifstream textFile(_filePath, std::ios::in);
        if (!textFile.is_open())
            return "";
        std::string buffer, line;
        while (!textFile.eof())
        {
            std::getline(textFile, line);
            buffer += line + '\n';
        }
        return buffer;
    }
}

namespace br::gl
{
    const Status CreateWindowContext(SDL_Window*& _window, const char* _windowName, const int& _windowWidth, const int& _windowHeight)
    {
        _window = SDL_CreateWindow(_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
        if (_window == nullptr)
            return Status::ERROR_WINDOW_CREATION;

        SDL_GLContext sdlGLContext = SDL_GL_CreateContext(_window);
        if (sdlGLContext == nullptr)
            return Status::ERROR_GLCONTEXT_INIT;

        GLenum glewStatus = glewInit();
        if (glewStatus != GLEW_OK)
            return Status::ERROR_GLEW_INIT;

        return Status::OK;
    }

    void ShaderProgram::AddShader(const GLuint& _shaderID)
    {
        shaderObjects.push_back(_shaderID);
        glAttachShader(shaderProgramID, _shaderID);
    }

    const GLuint ShaderProgram::CompileShader(const GLenum& _shaderType, const char* _source)
    {
        GLuint shaderID;
        if (gl::CompileShader(shaderID, _shaderType, _source) == gl::Status::OK)
            AddShader(shaderID);
        return shaderID;
    }

    const Status ShaderProgram::Link()
    {
        glLinkProgram(shaderProgramID);
        GLint success = 0;
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, (int *)&success);
        isLinked = success != GL_FALSE;
        return success == GL_FALSE ? Status::ERROR_SHADER_COMPILATION : Status::OK;
    }

    ShaderProgram::ShaderProgram()
    {
        shaderProgramID = glCreateProgram();
    }
    ShaderProgram::~ShaderProgram()
    {
        for (GLuint shaderID : shaderObjects)
        {
            glDetachShader(shaderProgramID, shaderID);
            glDeleteShader(shaderProgramID);
        }
        shaderObjects.clear();
        glDeleteProgram(shaderProgramID);
    }

    const Status CompileShader(GLuint& _shaderID, const GLenum& _shaderType, const char* _source)
    {
        _shaderID = glCreateShader(_shaderType);
        glShaderSource(_shaderID, 1, &_source, NULL);
        glCompileShader(_shaderID);
        GLint success = 0;
        glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
        return success == GL_FALSE ? Status::ERROR_SHADER_COMPILATION : Status::OK;
    }

    std::string GetShaderStatus(const GLuint& _shaderID)
    {
        GLint max = 0;
        glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &max);
        std::string buffer;
        buffer.resize(max);
        glGetShaderInfoLog(_shaderID, max, &max, &buffer[0]);
        return buffer;
    }

    std::string GetProgramStatus(const GLuint& _programID)
    {
        GLint max = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &max);
        std::string buffer;
        buffer.resize(max);
        glGetProgramInfoLog(_programID, max, &max, &buffer[0]);
        return buffer;
    }
}