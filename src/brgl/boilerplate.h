#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

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
        ERROR_SHADER_COMPILATION,
        OK
    };

    class ShaderProgram
    {
    public:
        void AddShader(const GLuint& _shaderID);
        const GLuint CompileShader(const GLenum& _shaderType, const char* _source);
        const Status Link();
        const GLuint GetID() { return shaderProgramID; }
        const bool IsLinked() { return isLinked; }
        void Bind() { glUseProgram(shaderProgramID); }
        void Unbind() { glUseProgram(0); }

    public:
        const GLint operator[](const char* _uniformName);

    private:
        GLuint shaderProgramID;
        std::vector<GLuint> shaderObjects;
        bool isLinked;

    public:
        ShaderProgram();
        ~ShaderProgram();
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
    };
    const Status CompileShader(GLuint& _shaderID, const GLenum& _shaderType, const char* _source);
    std::string GetShaderStatus(const GLuint& _shaderID);
    std::string GetProgramStatus(const GLuint& _programID);

    template <typename T>
    class BufferObject
    {
    public:
        void SetData(const std::vector<T>& _bufferData) { bufferData = _bufferData; }
        void SetAttributes(const GLuint& _layout, const GLenum& _normalizedData = GL_FALSE)
        {
            layout = _layout;
            normalizedData = _normalizedData;
        }
        const size_t GetSize() { return bufferData.size(); }
        const GLuint GetID() { return bufferID; }
        void Bind() { glBindBuffer(bufferType, bufferID); }
        void Unbind() { glBindBuffer(bufferType, 0); }

    public:
        T& operator[](const size_t& _index) { return bufferData[_index]; }

    private:
        void Release() { if (bufferID == 0) return; glDeleteBuffers(1, &bufferID); bufferID = 0; }

    private:
        friend class VertexArrayObject;
        friend class BufferObjectHandle;
        std::vector<T> bufferData;
        GLuint bufferID;
        GLenum bufferType;
        GLuint layout;
        GLenum dataType;
        GLenum normalizedData;

    public:
        BufferObject()
        {
            dataType = GL_FLOAT;
            bufferType = GL_ARRAY_BUFFER;
            bufferID = 0;
            SetAttributes(0);
        }
        BufferObject(const std::vector<T>& _bufferData, const GLenum& _dataType, const GLuint& _layout = 0, const GLenum& _bufferType = GL_ARRAY_BUFFER) 
        { 
            dataType = _dataType;
            bufferType = _bufferType;
            SetData(_bufferData);
            SetAttributes(_layout);
            glGenBuffers(1, &bufferID);
        }
        void operator=(BufferObject<T>& _other)
        {
            if (this != &_other)
            {
                Release();
                std::swap(bufferData, _other.bufferData);
                std::swap(bufferID, _other.bufferID);
                bufferType = _other.bufferType;
                dataType = _other.dataType;
                SetAttributes(_other.layout, _other.normalizedData);
            }
        }
        ~BufferObject() { Release(); }
        BufferObject(const BufferObject&) = delete;
        BufferObject& operator=(const BufferObject&) = delete;
    };

    class BufferObjectHandle
    {
    public:
        const GLuint GetID() { return bufferID; }
        template<typename T>
        void operator=(BufferObject<T>& _bufferObject)
        {
            Release();
            std::swap(bufferID, _bufferObject.bufferID);
        }

    private:
        void Release() { if (bufferID == 0) return; glDeleteBuffers(1, &bufferID); bufferID = 0; }

    private:
        GLuint bufferID;

    public:
        BufferObjectHandle() : bufferID{ 0 } { }
        ~BufferObjectHandle() { Release(); }
        BufferObjectHandle(const BufferObjectHandle&) = delete;
        BufferObjectHandle& operator=(const BufferObjectHandle&) = delete;
    };

    const GLuint CreateVertexArrayObject();

    class VertexArrayObject
    {
    public:
        template<typename T>
        void LinkBufferObject(const BufferObject<T>& _bufferObject, const GLuint& _sizePerVertex, const GLenum& _drawType = GL_STATIC_DRAW);
        template<typename T, typename V>
        void LinkBufferObject(const BufferObject<T>& _bufferObject, const BufferObject<V>& _elementObject, const GLuint& _sizePerVertex, const GLenum& _drawType = GL_STATIC_DRAW);
        const GLuint GetID() { return vaoID; }
        void Bind() { glBindVertexArray(vaoID); }
        void Unbind() { glBindVertexArray(0); }
    
    private:
        GLuint vaoID;

    public:
        VertexArrayObject();
        ~VertexArrayObject();
        VertexArrayObject(const VertexArrayObject&) = delete;
        VertexArrayObject& operator=(const VertexArrayObject&) = delete;
    };

    const GLuint CreateTexture2D(unsigned char* _textureData, const GLint& _width, const GLint& _height, const GLenum& _format);
};

namespace br::gl
{
    template<typename T>
    void VertexArrayObject::LinkBufferObject(const BufferObject<T>& _bufferObject, const GLuint& _sizePerVertex, const GLenum& _drawType)
    {
        glBindVertexArray(vaoID);
        glBindBuffer(_bufferObject.bufferType, _bufferObject.bufferID);
        glBufferData(_bufferObject.bufferType, _bufferObject.bufferData.size() * sizeof(T), &_bufferObject.bufferData.front(), _drawType);
        glVertexAttribPointer(_bufferObject.layout, _sizePerVertex, _bufferObject.dataType, _bufferObject.normalizedData, 0, NULL);
        glEnableVertexAttribArray(_bufferObject.layout);
        glBindBuffer(_bufferObject.bufferType, 0);
        glBindVertexArray(0);
    };

    template<typename T, typename V>
    void VertexArrayObject::LinkBufferObject(const BufferObject<T>& _bufferObject, const BufferObject<V>& _elementObject, const GLuint& _sizePerVertex, const GLenum& _drawType)
    {
        glBindVertexArray(vaoID);
        glBindBuffer(_bufferObject.bufferType, _bufferObject.bufferID);
        glBufferData(_bufferObject.bufferType, _bufferObject.bufferData.size() * sizeof(T), &_bufferObject.bufferData.front(), _drawType);
        glBindBuffer(_elementObject.bufferType, _elementObject.bufferID);
        glBufferData(_elementObject.bufferType, _elementObject.bufferData.size() * sizeof(V), &_elementObject.bufferData.front(), _drawType);
        glVertexAttribPointer(_bufferObject.layout, _sizePerVertex, _bufferObject.dataType, _bufferObject.normalizedData, 0, NULL);
        glEnableVertexAttribArray(_bufferObject.layout);
        glBindBuffer(_bufferObject.bufferType, 0);
        glBindVertexArray(0);
    };
}