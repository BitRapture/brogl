#pragma once
#include "boilerplate.h"

#include <iostream>

namespace br::gl
{
    // class Triangle
    class Quad
    {
    public:
        void Draw()
        {
            glBindVertexArray(vao.GetID());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    private:
        BufferObject<float> vertices;
        BufferObject<unsigned int> indices;
        VertexArrayObject vao;

    public:
        Quad(const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight)
        {
            vertices = BufferObject<float>({
                _normX + _normWidth, _normY + _normHeight, 0.0f,
                _normX + _normWidth, _normY, 0.0f,
                _normX, _normY, 0.0f,
                _normX, _normY + _normHeight, 0.0f
            }, GL_FLOAT, 0, GL_ARRAY_BUFFER);
            indices = BufferObject<unsigned int>({
                0, 1, 3,
                1, 2, 3
            }, GL_UNSIGNED_INT, 0, GL_ELEMENT_ARRAY_BUFFER);

            vao.LinkBufferObject(vertices, indices, 3);
        }
    };
    // class Mesh313
}