#pragma once

#include "FBGL.hpp"

class FBGL_API IndexBuffer2D
{
public:
    IndexBuffer2D(uint32_t m_NumIndices, uint8_t elementSize, GLenum usage, void* data);
    ~IndexBuffer2D();


    GLuint GetBufferID() const
    {
        return m_bufferID;
    }


    void bind();
    void unbind();

private:

    void GenerateBuffer();


    GLuint m_bufferID;

    GLenum m_usage;
    uint8_t m_elementSize;
    void* m_data;
    uint32_t m_NumIndices;

};
