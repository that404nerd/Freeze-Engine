#version 420 core

out vec4 o_PlayerColor;
uniform vec4 u_Color;

void main()
{
    o_PlayerColor = vec4(u_Color);
}