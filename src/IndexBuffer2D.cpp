#include "IndexBuffer2D.hpp"


IndexBuffer2D::IndexBuffer2D(uint32_t NumIndices, uint8_t elementSize, GLenum usage, void* data)
{

    this->m_NumIndices = NumIndices;
    this->m_elementSize = elementSize;
    this->m_usage = usage;
    this->m_data = data;

    GenerateBuffer();
}
IndexBuffer2D::~IndexBuffer2D()
{

}
void IndexBuffer2D::GenerateBuffer()
{
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndices * sizeof(m_elementSize), m_data, m_usage);


}
void IndexBuffer2D::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}
void IndexBuffer2D::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
