#pragma once

#include "FBGL.hpp"


class FBGL_API VertexBuffer2D
{
public:
    VertexBuffer2D(uint32_t numVerts, GLenum usage, Vertex2D* data);
    ~VertexBuffer2D();


    //binder
    void bind();

    void unbind();

    //Getter
    inline GLuint GetBufferID() const
    {
        return m_bufferID;
    }
    inline GLuint GetVAO() const
    {
        return m_vao;
    }
    inline uint32_t GetNumVerts() const
    {
        return m_numVerts;
    }

    inline GLenum GetUsage() const
    {
        return m_usage;
    }

    //Can return nullptr!
    inline Vertex2D* GetVertexData() const
    {
        return m_data;
    }

private:

    void CreateVertexBuffer();


    GLuint m_bufferID;
    GLuint m_vao;

    uint32_t m_numVerts;
    GLenum m_usage;
    Vertex2D* m_data;

};
