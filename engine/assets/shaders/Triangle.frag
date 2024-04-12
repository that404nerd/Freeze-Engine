#version 420 core

out vec4 o_TriangleColor;
in vec4 f_TriangleColor;

void main()
{
    o_TriangleColor = f_TriangleColor;
}