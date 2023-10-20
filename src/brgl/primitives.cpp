#include "primitives.h"

namespace br::gl
{
    void Quad::Render()
    {
        glBindVertexArray(vao.GetID());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    Quad::Quad(const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight)
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

    void Sprite::Render()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBindVertexArray(vao.GetID());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Sprite::Sprite(unsigned char* _textureData, const GLint& _texWidth, const GLint& _texHeight, const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight)
        : Quad(_normX, _normY, _normWidth, _normHeight)
    {
        textureID = CreateTexture2D(_textureData, _texWidth, _texHeight, GL_RGBA);
        texCoords = BufferObject<float>({
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        }, GL_FLOAT, 1);
        vao.LinkBufferObject(texCoords, 2);
    }

}