#version 330 core

layout(location = 0) in vec2 a_location;
layout(location = 1) in vec4 a_color;


out vec4 of_color;

void main()
{
    gl_Position = vec4(a_location, 0.f, 1.f);
    of_color = a_color;
}
