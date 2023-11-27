#include "boilerplate.h"
#include <fstream>

namespace br
{
    std::string open_text_file(const char* _filePath)
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
    void ShaderProgram::add_shader(const GLuint& _shaderID)
    {
        shaderObjects.push_back(_shaderID);
        glAttachShader(shaderProgramID, _shaderID);
    }

    const GLuint ShaderProgram::compile_shader(const GLenum& _shaderType, const char* _source)
    {
        GLuint shaderID;
        if (gl::compile_shader(shaderID, _shaderType, _source) == gl::Status::OK)
            add_shader(shaderID);
        return shaderID;
    }

    const Status ShaderProgram::link()
    {
        glLinkProgram(shaderProgramID);
        GLint success = 0;
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, (int *)&success);
        isLinked = success != GL_FALSE;
        if (isLinked)
        {
            for (GLuint shaderID : shaderObjects)
                glDeleteShader(shaderID);
            shaderObjects.clear();
        }
        return success == GL_FALSE ? Status::ERROR_SHADER_COMPILATION : Status::OK;
    }

    const GLint ShaderProgram::operator[](const char* _uniformName)
    {
        return glGetUniformLocation(shaderProgramID, _uniformName);
    }

    ShaderProgram::ShaderProgram()
    {
        shaderProgramID = glCreateProgram();
    }
    ShaderProgram::~ShaderProgram()
    {
        shaderObjects.clear();
        glDeleteProgram(shaderProgramID);
    }

    const Status compile_shader(GLuint& _shaderID, const GLenum& _shaderType, const char* _source)
    {
        _shaderID = glCreateShader(_shaderType);
        glShaderSource(_shaderID, 1, &_source, NULL);
        glCompileShader(_shaderID);
        GLint success = 0;
        glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
        return success == GL_FALSE ? Status::ERROR_SHADER_COMPILATION : Status::OK;
    }

    std::string get_shader_status(const GLuint& _shaderID)
    {
        GLint max = 0;
        glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &max);
        std::string buffer;
        buffer.resize(max);
        glGetShaderInfoLog(_shaderID, max, &max, &buffer[0]);
        return buffer;
    }

    std::string get_program_status(const GLuint& _programID)
    {
        GLint max = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &max);
        std::string buffer;
        buffer.resize(max);
        glGetProgramInfoLog(_programID, max, &max, &buffer[0]);
        return buffer;
    }

    const GLuint create_vertex_array_object()
    {
        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        return vaoID;
    }

    VertexArrayObject::VertexArrayObject()
    {
        vaoID = create_vertex_array_object();
    }
    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &vaoID);
    }

    const GLuint create_texture_2d(unsigned char* _textureData, const GLint& _width, const GLint& _height, const GLenum& _format)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Wrapping (move at some point)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, _textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        return textureID;
    }
}