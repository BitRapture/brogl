#include "primitives.h"

namespace br::gl
{
    void BasicQuad::Render()
    {
        glBindVertexArray(vao.GetID());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    BasicQuad::BasicQuad(const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight)
    {
        BufferObject<float> verticesBuffer({
            _normX + _normWidth, _normY + _normHeight, 0.0f,
            _normX + _normWidth, _normY, 0.0f,
            _normX, _normY, 0.0f,
            _normX, _normY + _normHeight, 0.0f
        }, GL_FLOAT, 0, GL_ARRAY_BUFFER);
        BufferObject<unsigned int> indicesBuffer({
            0, 1, 3,
            1, 2, 3
        }, GL_UNSIGNED_INT, 0, GL_ELEMENT_ARRAY_BUFFER);
        vao.LinkBufferObject(verticesBuffer, indicesBuffer, 3);

        vertices = verticesBuffer;
        indices = indicesBuffer;
    }

    void BasicSprite::Render()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBindVertexArray(vao.GetID());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    BasicSprite::BasicSprite(unsigned char* _textureData, const GLint& _texWidth, const GLint& _texHeight, const float& _normX, const float& _normY, const float& _normWidth, const float& _normHeight)
        : BasicQuad(_normX, _normY, _normWidth, _normHeight)
    {
        textureID = CreateTexture2D(_textureData, _texWidth, _texHeight, GL_RGBA);
        BufferObject<float> texCoordsBuffer({
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        }, GL_FLOAT, 1);
        vao.LinkBufferObject(texCoordsBuffer, 2);

        texCoords = texCoordsBuffer;
    }

}