#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

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

    const Status CreateWindowContext(SDL_Window*& _window, SDL_GLContext& _glContext, const char* _windowName, const int& _windowWidth, const int& _windowHeight);

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

    template <typename T>
    class BufferObject
    {
    public:
        void SetAttributes(const GLuint& _layout, const GLenum& _normalizedData = GL_FALSE, const GLsizei& _stride = 0)
        {
            layout = _layout;
            normalizedData = _normalizedData;
            stride = _stride;
        }
        const size_t GetSize() { return bufferData.size(); }

    public:
        T& operator[](const size_t& _index) { return bufferData[_index]; }

    private:
        friend class VertexArrayObject;
        std::vector<T> bufferData;
        GLuint bufferID;
        GLenum bufferType;
        GLuint layout;
        GLenum dataType;
        GLenum normalizedData;
        GLsizei stride;

    public:
        BufferObject(const std::vector<T>& _bufferData, GLenum _dataType, GLenum _bufferType = GL_ARRAY_BUFFER) 
        : bufferData{ _bufferData }, dataType{ _dataType }, bufferType{ _bufferType }
        { 
            SetAttributes(0); 
            glGenBuffers(1, &bufferID);
        }
        ~BufferObject() { }
    };

    const GLuint CreateVertexArrayObject();

    class VertexArrayObject
    {
    public:
        template<typename T>
        void LinkBufferObject(const BufferObject<T>& _bufferObject, const GLuint& _vertices, const GLenum& _drawType = GL_STATIC_DRAW);
        const GLuint GetID() { return vaoID; }
    
    private:
        GLuint vaoID;

    public:
        VertexArrayObject();
        ~VertexArrayObject();
    };
};

namespace br::gl
{
    template<typename T>
    void VertexArrayObject::LinkBufferObject(const BufferObject<T>& _bufferObject, const GLuint& _vertices, const GLenum& _drawType)
    {
        glBindVertexArray(vaoID);
        glBindBuffer(_bufferObject.bufferType, _bufferObject.bufferID);
        glBufferData(_bufferObject.bufferType, _bufferObject.bufferData.size() * sizeof(T), &_bufferObject.bufferData.front(), _drawType);
        glVertexAttribPointer(
            _bufferObject.layout, _vertices, _bufferObject.dataType, _bufferObject.normalizedData,
            _bufferObject.stride, NULL
            );
        glEnableVertexAttribArray(_bufferObject.layout);
        glBindBuffer(_bufferObject.bufferType, 0);
        glBindVertexArray(0);
    };
};