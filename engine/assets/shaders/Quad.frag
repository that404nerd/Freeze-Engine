#version 420 core

out vec4 o_QuadColor;
in vec4 f_Color;

void main()
{
    o_QuadColor = f_Color;
}