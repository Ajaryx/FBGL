#version 330 core

layout(location = 0) out vec4 o_color;


in vec4 of_color;

void main()
{
    o_color = of_color;
}
