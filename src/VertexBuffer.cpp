#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer()
{
    glewInit();

    glVertex2f(0.F, 0.F);
}

VertexBuffer::~VertexBuffer()
{
}
