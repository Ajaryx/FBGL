#include "VertexBuffer.hpp"
#include <iostream>

VertexBuffer2D::VertexBuffer2D(uint32_t numVerts, GLenum target, GLenum usage, Vertex2D* data)
{
    this->m_numVerts = numVerts;
    this->m_target = target;
    this->m_usage = usage;
    this->m_data = data;

    CreateVertexBuffer();
}

VertexBuffer2D::~VertexBuffer2D()
{

    bind();
    glDeleteBuffers(1, &m_bufferID);

}

void VertexBuffer2D::CreateVertexBuffer()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_bufferID);
    glBindBuffer(m_target, m_bufferID);

    glBufferData(m_target, m_numVerts * sizeof(Vertex2D), static_cast<void*>(m_data), m_usage);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), reinterpret_cast<void*>(offsetof(struct Vertex2D, x)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), reinterpret_cast<void*>(offsetof(struct Vertex2D, r)));

    unbind();
}
void VertexBuffer2D::bind()
{
    glBindVertexArray(m_vao);

}
void VertexBuffer2D::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(m_target, 0);
}
