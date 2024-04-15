#version 420 core

layout (location = 0) in vec3 a_QuadPos;
layout (location = 1) in vec4 a_QuadColor;

out vec4 f_Color;

uniform mat4 a_ProjectionMatrix;

void main()
{
    gl_Position = a_ProjectionMatrix * vec4(a_QuadPos, 1.0f);
    f_Color = a_QuadColor;
}