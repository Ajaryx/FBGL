#pragma once
#include "FBGL_Export.hpp"
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>

struct FBGL_API Vertex2D
{
    float x;
    float y;

    float r;
    float g;
    float b;
    float a;
};
enum FBGL_API ShaderState : uint8_t
{
    ESS_SHADER_OK = 0x00,
    ESS_SHADER_COMPILE_ERROR = 1 << 0,
    EES_SHADER_NO_SRC = 1 << 1
};
