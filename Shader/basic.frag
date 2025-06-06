#version 330 core

layout(location = 0) out vec4 o_color;


in vec4 of_color;
in vec2 of_texCoord;

uniform sampler2D u_texture;

void main()
{
    vec4 texColor = texture(u_texture, of_texCoord);
    o_color = texColor;
}
