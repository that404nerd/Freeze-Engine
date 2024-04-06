#version 420 core

out vec4 o_TriangleColor;
uniform vec4 u_Color;

void main()
{
    o_TriangleColor = vec4(u_Color);
}