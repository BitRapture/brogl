#pragma once
#include "boilerplate.h"

#include <iostream>

namespace br::gl
{
    // class Triangle
    class Quad
    {
    public:
        virtual void Render();

    protected:
        BufferObject<float> vertices;
        BufferObject<unsigned int> indices;
        VertexArrayObject vao;

    public:
        Quad(const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight);
    };

    class Sprite : public Quad
    {
    public:
        void Render() override;

    private:
        GLuint textureID;
        BufferObject<float> texCoords;

    public:
        Sprite(unsigned char* _textureData, const GLint& _texWidth, const GLint& _texHeight, const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight);
    };
    // class Mesh
}