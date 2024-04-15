#version 420 core

layout (location = 0) in vec3 a_PlayerPos;

uniform mat4 a_ProjectionMatrix;
uniform mat4 a_NewPosMatrix;

void main()
{
    gl_Position = a_ProjectionMatrix * a_NewPosMatrix * vec4(a_PlayerPos, 1.0f);
}