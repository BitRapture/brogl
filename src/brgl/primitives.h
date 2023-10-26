#pragma once
#include "boilerplate.h"

#include <iostream>

namespace br::gl
{
    // class Triangle
    class BasicQuad
    {
    public:
        virtual void Render();

    protected:
        BufferObjectHandle vertices;
        BufferObjectHandle indices;
        VertexArrayObject vao;

    public:
        BasicQuad(const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight);
    };

    class BasicSprite : public BasicQuad
    {
    public:
        void Render() override;

    private:
        GLuint textureID;
        BufferObjectHandle texCoords;

    public:
        BasicSprite(const std::vector<unsigned char>& _textureData, const GLint& _texWidth, const GLint& _texHeight, const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight);
    };
    // class Mesh
}