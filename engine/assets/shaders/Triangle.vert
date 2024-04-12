#version 420 core

layout (location = 0) in vec3 a_TrianglePos;
layout (location = 1) in vec4 a_TriangleColor;

out vec4 f_TriangleColor;

// uniform mat4 a_ProjectionMatrix;

void main()
{
    gl_Position = vec4(a_TrianglePos, 1.0f);
    f_TriangleColor = a_TriangleColor;
}